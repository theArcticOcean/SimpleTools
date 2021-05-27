#include "filesManager.h"
#include "ULog.h"
#include "IOBase.h"

#ifdef Q_OS_UNIX
#include <dirent.h>
#include <unistd.h>
#endif

#include <QDir>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vtkImageStencil.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageMarchingCubes.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkLookupTable.h>
#include <vtkFillHolesFilter.h>
#include <vtkScalarsToColors.h>
#include <vtkPolyDataNormals.h>
#include <vtkImageToPolyDataFilter.h>
#include <vtkImageQuantizeRGBToIndex.h>
#include <vtkTriangleFilter.h>

bool filesManager::endsWith(const std::string &mainStr, const std::string &toMatch)
{
    if( mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

filesManager::filesManager()
{
    m_ImageInval = 255;
    m_ImageOutval = 0;
    m_ImageSpaceVal = 0.05;
}

std::string filesManager::GetBaseName(std::string filePath)
{
    int found = filePath.find_last_of(".");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}

std::string filesManager::GetFolderName(std::string filePath)
{
    int found = filePath.find_last_of("/");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}

int filesManager::RemoveDir(const char *dir)
{
    QDir qdir( dir );
    qdir.removeRecursively();
    return 0;
}

vtkSmartPointer<vtkImageData> filesManager::ConvertPolydataToImage(vtkPolyData *polydata)
{
    double bounds[6];
    polydata->GetBounds(bounds);

    int dim[3];
    for (int i = 0; i < 3; i++)
    {
        dim[i] = static_cast<int>( ceil((bounds[2 * i + 1] - bounds[2 * i]) / m_ImageSpaceVal) );
    }
    double origin[3];
    origin[0] = bounds[0] + m_ImageSpaceVal / 2;
    origin[1] = bounds[2] + m_ImageSpaceVal / 2;
    origin[2] = bounds[4] + m_ImageSpaceVal / 2;

    vtkSPtrNew(imageData, vtkImageData)
    imageData->SetSpacing(m_ImageSpaceVal, m_ImageSpaceVal, m_ImageSpaceVal);
    imageData->SetDimensions(dim);
    imageData->SetOrigin(origin);
    imageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    imageData->SetExtent( 0, dim[0] - 1, 0, dim[1] - 1, 0, dim[2] - 1 );

    // fill the imageData with foreground voxels
    vtkIdType count = imageData->GetNumberOfPoints();
    for (vtkIdType i = 0; i < count; ++i)
    {
        imageData->GetPointData()->GetScalars()->SetTuple1(i, m_ImageInval);
    }

    // polygonal data --> imageData stencil:
    vtkSPtrNew(pd2stenc, vtkPolyDataToImageStencil);
    pd2stenc->SetInputData(polydata);
    pd2stenc->SetOutputOrigin(origin);
    pd2stenc->SetOutputSpacing(m_ImageSpaceVal, m_ImageSpaceVal, m_ImageSpaceVal);
    pd2stenc->SetOutputWholeExtent(imageData->GetExtent());
    pd2stenc->Update();

    // cut the corresponding white imageData and set the background:
    vtkSPtrNew(imgstenc, vtkImageStencil);
    imgstenc->SetInputData(imageData);
    imgstenc->SetStencilConnection(pd2stenc->GetOutputPort());
    imgstenc->ReverseStencilOff();
    imgstenc->SetBackgroundValue( m_ImageOutval );
    imgstenc->Update();

    imageData->DeepCopy(imgstenc->GetOutput());
    return imageData;
}

vtkSmartPointer<vtkPolyData> filesManager::ConvertImageToPolydata(vtkImageData *imageData)
{
    vtkSPtrNew( marchingCubes, vtkImageMarchingCubes );
    marchingCubes->SetInputData( imageData );
    marchingCubes->SetValue( 0, (m_ImageInval + m_ImageOutval)/2 );
    marchingCubes->SetNumberOfContours( 1 );
    marchingCubes->Update();

    Log( IInfo, "number cell: ", marchingCubes->GetOutput()->GetNumberOfCells() );

    // Fill the holes
    auto fillHoles = vtkSmartPointer<vtkFillHolesFilter>::New();
    fillHoles->SetInputConnection( marchingCubes->GetOutputPort() );
    fillHoles->SetHoleSize(1000.0);
    fillHoles->Update();

    // Make the triangle winding order consistent
    auto normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputConnection(fillHoles->GetOutputPort());
    normals->ConsistencyOn();
    normals->SplittingOff();
    normals->Update();
    normals->GetOutput()->GetPointData()->SetNormals(
        marchingCubes->GetOutput()->GetPointData()->GetNormals());

    vtkSPtrNew( polyData, vtkPolyData );
    polyData->DeepCopy( normals->GetOutput() );

    Log( IInfo, "polyData cell count: ", polyData->GetNumberOfCells() );
    return polyData;
}
