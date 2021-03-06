#include "facetIO.h"

#include <vtkFacetWriter.h>
#include <vtkFacetReader.h>
#include <unistd.h>

facetIO::facetIO()
{

}

facetIO::~facetIO()
{

}

bool facetIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkFacetReader> reader = vtkSmartPointer<vtkFacetReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string facetIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkFacetWriter> writer = vtkSmartPointer<vtkFacetWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
