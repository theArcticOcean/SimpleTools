#include "gltfIO.h"

#include <vtkGLTFDocumentLoader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

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

void gltfIO::Read(std::string filePath)
{
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

    importer->SetFileName( filePath.c_str() );
    importer->SetRenderWindow( renderWindow );
    importer->Read();

    m_Data = importer->GetMesh();
}

void gltfIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
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
    exporter->SetFileName( filePath.c_str() );
    exporter->Write();
}
