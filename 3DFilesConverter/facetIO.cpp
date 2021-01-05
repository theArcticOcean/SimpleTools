#include "facetIO.h"

#include <vtkFacetWriter.h>
#include <vtkFacetReader.h>

facetIO::facetIO()
{

}

facetIO::~facetIO()
{

}

void facetIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkFacetReader> reader = vtkSmartPointer<vtkFacetReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();
}

void facetIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    vtkSmartPointer<vtkFacetWriter> writer = vtkSmartPointer<vtkFacetWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();
}
