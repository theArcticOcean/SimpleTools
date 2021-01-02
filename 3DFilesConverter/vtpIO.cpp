#include "vtpIO.h"

#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

vtpIO::vtpIO()
{

}

vtpIO::~vtpIO()
{

}

void vtpIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();
}

void vtpIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();
}
