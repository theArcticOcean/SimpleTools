#include <QFileInfo>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>

#include "plyIO.h"
#include "ULog.h"
#include "filesManager.h"

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

plyIO::plyIO()
{

}

plyIO::~plyIO()
{

}

bool plyIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();
    return true;
}

std::string plyIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    QFileInfo file( filePath.c_str() );
    if( file.exists() )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkPLYWriter> writer = vtkSmartPointer<vtkPLYWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
