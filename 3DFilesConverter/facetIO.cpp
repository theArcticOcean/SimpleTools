#include "facetIO.h"

#include <vtkFacetWriter.h>
#include <vtkFacetReader.h>
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif
#include <QFileInfo>

facetIO::facetIO()
{

}

facetIO::~facetIO()
{

}

bool facetIO::Read(std::string filePath)
{
    vtkSmartPointer<vtkFacetReader> reader = vtkSmartPointer<vtkFacetReader>::New();
    reader->SetFileName( filePath.c_str() );
    reader->Update();

    m_Data = reader->GetOutput();

    return true;
}

std::string facetIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    QFileInfo file( filePath.c_str() );
    if( file.exists() )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

    vtkSmartPointer<vtkFacetWriter> writer = vtkSmartPointer<vtkFacetWriter>::New();
    writer->SetInputData( data );
    writer->SetFileName( filePath.c_str() );
    writer->Write();

    return filePath;
}
