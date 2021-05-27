#include "vtpIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

#include <QDir>
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
    auto newFilePath = baseName + ".vtp";

    QFileInfo file( newFilePath.c_str() );
    if( file.exists() )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( newFilePath.c_str() );
    }

    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( newFilePath.c_str() );
    writer->Write();

    return newFilePath;
}
