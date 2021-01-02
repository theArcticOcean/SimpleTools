#include "vtkIO.h"

#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>

vtkIO::vtkIO()
{

}

vtkIO::~vtkIO()
{

}

void vtkIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();
}

void vtkIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();
}
