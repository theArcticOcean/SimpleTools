#include "3DSIO.h"

#include <vtk3DSImporter.h>
#include <vtkMapper.h>
#include <vtkAppendPolyData.h>

w3DSIO::w3DSIO()
{

}

w3DSIO::~w3DSIO()
{

}

bool w3DSIO::Read(std::string filePath)
{
    vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
    importer->SetFileName( filePath.c_str() );
    importer->ComputeNormalsOn();
    importer->Read();

    //auto data = ren->GetActors()->GetLastItem()->GetMapper()->GetInput();
    vtk3DSMesh *ptr = importer->MeshList;
    vtkSmartPointer<vtkAppendPolyData> appendPd = vtkSmartPointer<vtkAppendPolyData>::New();
    while( ptr )
    {
        vtkPolyData *data = ptr->aPolyData;
        appendPd->AddInputData( data );
        ptr = (vtk3DSMesh *)( ptr->next );
    }
    appendPd->Update();
    m_Data->DeepCopy( appendPd->GetOutput() );
    if( m_Data && m_Data->GetNumberOfCells() > 0 )
    {
        return true;
    }
    return false;
}

std::string w3DSIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    return "";
}
