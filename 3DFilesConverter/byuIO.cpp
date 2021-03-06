#include "byuIO.h"
#include "filesManager.h"
#include "ULog.h"

#include <sys/stat.h>
#include <unistd.h>
#include <vtkBYUReader.h>
#include <vtkBYUWriter.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

byuIO::byuIO()
{

}

byuIO::~byuIO()
{

}

/*
*   read folder to create a complete polydata.
*/
bool byuIO::Read(std::string filePath)
{
    std::string folderPath;
    // unzip compressed file.
    if( filesManager::GetInstance()->endsWith( filePath, ".zip" ) )
    {
        folderPath = filesManager::GetInstance()->GetBaseName( filePath );
        if ( access( folderPath.c_str(), F_OK ) == 0 )
        {
            filesManager::GetInstance()->RemoveDir( folderPath.c_str() );
        }
        folderPath = filesManager::GetInstance()->unzip( filePath );
    }
    else {
        Log( IError, "not zip file." );
        return false;
    }

    Log( IInfo, "folderPath: ", folderPath );

    vtkSPtrNew( reader, vtkBYUReader );
    std::string tmp = "";
    if( filesManager::GetInstance()->FindFilePath( ".g", folderPath, tmp ) )
    {
        reader->SetGeometryFileName( tmp.c_str() );
    }
    else if( filesManager::GetInstance()->FindFilePath( ".s", folderPath, tmp ) )
    {
        reader->SetScalarFileName( tmp.c_str() );
    }
    else if( filesManager::GetInstance()->FindFilePath( ".d", folderPath, tmp ) )
    {
        reader->SetDisplacementFileName( tmp.c_str() );
    }
    else if( filesManager::GetInstance()->FindFilePath( ".t", folderPath, tmp ) )
    {
        reader->SetTextureFileName( tmp.c_str() );
    }
    reader->Update();

    if( reader->GetOutput()->GetNumberOfCells() <= 0 )
    {
        Log( IError, "not valid polydata" );
        return false;
    }

    m_Data->DeepCopy( reader->GetOutput() );

    return true;
}

std::string byuIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
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
        return "NAN.txt";
    }

    vtkSPtrNew( writer, vtkBYUWriter );
    writer->SetInputData( data );
    if( data->GetPointData()->GetScalars() || data->GetCellData()->GetScalars() ){
        auto tmp = baseName + "/result.s";
        writer->SetScalarFileName( tmp.c_str() );
    }
    writer->SetGeometryFileName( (baseName + "/result.g").c_str() );
    auto tmp = baseName + "/result.d";
    writer->SetDisplacementFileName( tmp.c_str() );
    tmp = baseName + "/result.t";
    writer->SetTextureFileName( tmp.c_str() );
    writer->Write();

    Log( IInfo, "baseName: ", baseName.c_str() );
    auto newFilePath = filesManager::GetInstance()->zip( baseName );
    return newFilePath;
}
