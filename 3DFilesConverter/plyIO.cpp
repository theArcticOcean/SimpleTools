#include "plyIO.h"

#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>

plyIO::plyIO()
{

}

plyIO::~plyIO()
{

}

void plyIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();
}

void plyIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    vtkSmartPointer<vtkPLYWriter> writer = vtkSmartPointer<vtkPLYWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();
}
