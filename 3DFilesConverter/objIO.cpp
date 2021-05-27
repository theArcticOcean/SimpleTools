#include "objIO.h"
#include "ULog.h"
#include "filesManager.h"

#include <vtkOBJReader.h>
#include <vtkOBJWriter.h>
#include <unistd.h>

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
    if ( access( filePath.c_str(), F_OK ) == 0 )
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
