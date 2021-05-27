#include "objIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkOBJReader.h>
#include <vtkOBJWriter.h>
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

#include <QFileInfo>

objIO::objIO()
{

}

objIO::~objIO()
{

}

bool objIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string objIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    QFileInfo file( filePath.c_str() );
    if( file.exists() )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkOBJWriter> writer = vtkSmartPointer<vtkOBJWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
