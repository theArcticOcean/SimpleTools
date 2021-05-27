#include "vtpIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <unistd.h>
#include <sys/stat.h>

vtpIO::vtpIO()
{

}

vtpIO::~vtpIO()
{

}

bool vtpIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string vtpIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
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
        return INVALID_FILE;
    }
    auto newFilePath = baseName + "/result.vtp";

    if ( access( newFilePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( newFilePath.c_str() );
    }

    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( newFilePath.c_str() );
    writer->Write();

    auto zipFilePath = filesManager::GetInstance()->zip( newFilePath );

    return zipFilePath;
}
