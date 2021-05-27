#include "stlIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <unistd.h>

stlIO::stlIO()
{

}

stlIO::~stlIO()
{

}

bool stlIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string stlIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
