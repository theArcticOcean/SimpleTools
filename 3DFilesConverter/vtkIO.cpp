#include "vtkIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <unistd.h>


vtkIO::vtkIO()
{

}

vtkIO::~vtkIO()
{

}

bool vtkIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string vtkIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
