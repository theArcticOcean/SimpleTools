#include "filesManager.h"
#include "ULog.h"
#include "IOBase.h"

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <zipper/zipper.h>
#include <zipper/unzipper.h>
#include <vtkImageStencil.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageMarchingCubes.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>

/*
*   use zipper library: https://github.com/sebastiandev/zipper
*   return folder path.
*/
std::string filesManager::unzip(std::string filePath)
{
    if( !endsWith( filePath, ".zip" ) )
    {
        return INVALID_FILE;
    }
    std::string baseName = filesManager::GetInstance()->GetBaseName( filePath );
    Log( IInfo, filePath, ", ", baseName );
    zipper::Unzipper unzipper( filePath );
    if( !unzipper.extract( baseName ) ){
        unzipper.close();
        return INVALID_FILE;
    }
    unzipper.close();
    return baseName;
}

/*
*   use zipper library: https://github.com/sebastiandev/zipper
*   return zip file path.
*/
std::string filesManager::zip(std::string folderPath)
{
    std::string zipPath = folderPath + ".zip";
    if ( access( zipPath.c_str(), F_OK ) == 0 )
    {
        RemoveDir( zipPath.c_str() );
    }
    zipper::Zipper zipper( zipPath );
    zipper.add( folderPath );
    zipper.close();
    return zipPath;
}

bool filesManager::FindFilePath(std::string suffix, std::string folderPath, std::string &result)
{
    DIR* dir = opendir( folderPath.c_str() );
    dirent* p = nullptr;
    std::string path = "";
    while( (p = readdir(dir)) != nullptr )
    {
        if( p->d_name[0] == '.' )
        {
            continue;
        }
        if( p->d_type == DT_DIR )
        {
            Log( IInfo, "p->d_name: ", (folderPath + "/" + p->d_name) );
            auto flag = FindFilePath( suffix, folderPath + "/" + p->d_name, result );
            if( flag ) {
                closedir(dir);
                return true;
            }
        }

        if( endsWith( p->d_name, suffix ) )
        {
            path = folderPath;
            while( endsWith( path, "/" ) )
            {
                path = path.substr(0, path.size() - 1);
            }
            path = path + "/" + p->d_name;
            result = path;
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    result = INVALID_FILE;
    return false;
}

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
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[128];
    DIR *dirp = nullptr;
    struct dirent *dp = nullptr;
    struct stat dir_stat;

    if ( 0 != access(dir, F_OK) )
    {
        return 0;
    }

    if ( 0 > stat(dir, &dir_stat) )
    {
        Log( IError, strerror(errno) );
        return -1;
    }

    if ( S_ISREG(dir_stat.st_mode) )
    {
        remove(dir);
    }
    else if ( S_ISDIR(dir_stat.st_mode) )
    {
        dirp = opendir(dir);
        while ( ( dp=readdir(dirp) ) != nullptr )
        {
            if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) ) {
                continue;
            }

            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            RemoveDir(dir_name);
        }
        closedir(dirp);

        rmdir( dir ); // delete empty dir
    }
    else
    {
        Log( IError, strerror(errno) );
    }
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

    // Fill the holes
    auto fillHoles = vtkSmartPointer<vtkFillHolesFilter>::New();
    fillHoles->SetInputConnection( marchingCubes->GetOutputPort() );
    fillHoles->SetHoleSize(1000.0);

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
    return polyData;
}
