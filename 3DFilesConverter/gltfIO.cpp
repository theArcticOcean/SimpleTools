#include "gltfIO.h"
#include "filesManager.h"
#include "ULog.h"

#include <vtkGLTFDocumentLoader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <sys/stat.h>

vtkStandardNewMacro(MyGLTFImporter);

vtkSmartPointer<vtkPolyData> MyGLTFImporter::GetMesh()
{
    auto model = this->Loader->GetInternalModel();
    if( model->Meshes.size() > 0 && model->Meshes[0].Primitives.size() > 0 )
    {
        return model->Meshes[0].Primitives[0].Geometry;
    }
    return nullptr;
}

gltfIO::gltfIO()
{

}

gltfIO::~gltfIO()
{

}

bool gltfIO::Read(std::string filePath)
{
    std::string folder;
    // unzip compressed file.
    if( filesManager::GetInstance()->endsWith( filePath, ".zip" ) )
    {
        folder = filesManager::GetInstance()->GetBaseName( filePath );
        if ( access( folder.c_str(), F_OK ) == 0 )
        {
            filesManager::GetInstance()->RemoveDir( folder.c_str() );
        }
        folder = filesManager::GetInstance()->unzip( filePath );
    }

    Log( IInfo, "folder: ", folder );
    std::string file_name = "NAN.txt";
    std::string tmp;
    if( filesManager::GetInstance()->FindFilePath( ".gltf", folder, tmp ) ) {
        file_name = tmp;
    }
    else {
        Log( IError, "not found gltf file" );
        return false;
    }

    Log( IInfo, "file_name: ", file_name );
    vtkSPtrNew( importer, MyGLTFImporter );

    vtkSPtrNew( mapper, vtkPolyDataMapper );

    vtkSPtrNew( actor, vtkActor );
    actor->SetMapper( mapper );

    vtkSPtrNew( renderer, vtkRenderer );
    renderer->AddActor(actor);
    renderer->SetBackground( 0, 0, 0 );

    vtkSPtrNew( renderWindow, vtkRenderWindow );
    renderWindow->AddRenderer( renderer );

    vtkSPtrNew( renderWindowInteractor, vtkRenderWindowInteractor );
    renderWindowInteractor->SetRenderWindow( renderWindow );

    importer->SetFileName( file_name.c_str() );
    importer->SetRenderWindow( renderWindow );
    importer->Read();

    m_Data = importer->GetMesh();

    return true;
}

/*
*   the parameter filePath looks like targetFinal_5057
*/
std::string gltfIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    auto baseName = filesManager::GetInstance()->GetBaseName( filePath );
    if ( access( baseName.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove dir" );
        filesManager::GetInstance()->RemoveDir( baseName.c_str() );
    }
    if ( mkdir( baseName.c_str(), 0777) )
    {
        Log( IError, strerror(errno) );
        return "NAN.txt";
    }
    auto newFilePath = baseName + "/result.gltf";

    // targetFinal_5057/result.gltf, argetFinal_5057/result
    Log( IDebug, newFilePath.c_str(), ", ", baseName.c_str() );

    vtkSPtrNew( exporter, vtkGLTFExporter );

    vtkSPtrNew( mapper, vtkPolyDataMapper );
    mapper->SetInputData( data );

    vtkSPtrNew( actor, vtkActor );
    actor->SetMapper( mapper );

    vtkSPtrNew( renderer, vtkRenderer );
    renderer->AddActor(actor);
    renderer->SetBackground( 0, 0, 0 );

    vtkSPtrNew( renderWindow, vtkRenderWindow );
    renderWindow->AddRenderer( renderer );

    exporter->SetRenderWindow( renderWindow );
    exporter->SetFileName( newFilePath.c_str() );
    exporter->Write();

    auto zipFilePath = filesManager::GetInstance()->zip( baseName );

    return zipFilePath;
}
