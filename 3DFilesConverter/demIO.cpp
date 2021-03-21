#include "demIO.h"

#include <vtkDEMReader.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageData.h>
#include <vtkWarpScalar.h>

demIO::demIO()
{

}

demIO::~demIO()
{

}

bool demIO::Read(std::string filePath)
{
    vtkSPtrNew( demReader, vtkDEMReader );
    demReader->SetFileName( filePath.c_str() );
    demReader->Update();

    // Extract geometry
    vtkSPtrNew( surface, vtkImageDataGeometryFilter );
    surface->SetInputData( demReader->GetOutput() );
    surface->Update();

    vtkSPtrNew( warp, vtkWarpScalar );
    warp->SetInputData( surface->GetOutput() );
    warp->SetScaleFactor(1);
    warp->UseNormalOn();
    warp->SetNormal(0, 0, 1);
    warp->Update();

    m_Data = dynamic_cast<vtkPolyData*>( warp->GetOutput() );

    return true;
}

std::string demIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    return "";
}
