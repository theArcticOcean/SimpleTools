#include "wrlIO.h"
#include "filesManager.h"
#include "ULog.h"

#include <vtkVRMLExporter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>

wrlIO::wrlIO()
{

}

wrlIO::~wrlIO()
{

}

bool wrlIO::Read(std::string filePath)
{
    return false;
}

std::string wrlIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSPtrNew( exporter, vtkVRMLExporter );
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
