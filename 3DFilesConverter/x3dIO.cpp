#include "x3dIO.h"
#include "filesManager.h"
#include "ULog.h"

#include <vtkX3DExporter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
x3dIO::x3dIO()
{

}

x3dIO::~x3dIO()
{

}

bool x3dIO::Read(std::string filePath)
{
    return false;
}

std::string x3dIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSPtrNew( exporter, vtkX3DExporter );
    vtkSPtrNew( mapper, vtkPolyDataMapper );
    mapper->SetInputData( data );
    vtkSPtrNew( actor, vtkActor );
    actor->SetMapper( mapper );
    vtkSPtrNew( renderer, vtkRenderer );
    renderer->AddActor( actor );
    vtkSPtrNew( renderWindow, vtkRenderWindow );
    renderWindow->AddRenderer( renderer );
    exporter->SetFileName( filePath.c_str() );
    exporter->SetActiveRenderer( renderer );
    exporter->SetRenderWindow( renderWindow );
    exporter->Write();

    return filePath;
}
