#include "tiffIO.h"
#include "filesManager.h"
#include "ULog.h"

#include <vtkTIFFWriter.h>
#include <vtkTIFFReader.h>
tiffIO::tiffIO()
{

}

tiffIO::~tiffIO()
{

}

bool tiffIO::Read(std::string filePath)
{
    vtkSPtrNew( reader, vtkTIFFReader );
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = filesManager::GetInstance()->ConvertImageToPolydata( reader->GetOutput() );
    if( m_Data && m_Data->GetNumberOfCells() > 0 )
    {
        return true;
    }
    return false;
}

std::string tiffIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSPtrNew( writer, vtkTIFFWriter );
    writer->SetFileName( filePath.c_str() );
    writer->SetInputData( filesManager::GetInstance()->ConvertPolydataToImage( data ) );
    writer->Write();

    return filePath;
}
