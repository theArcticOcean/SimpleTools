#include "ctmIO.h"

#include "point.hpp"

ctmIO::ctmIO()
{

}

ctmIO::~ctmIO()
{

}

void ctmIO::Read(std::string filePath)
{
    CTMimporter ctm;
    ctm.Load( filePath.c_str() );

    CTMuint vertCount = ctm.GetInteger(CTM_VERTEX_COUNT);
    const CTMfloat *vertices = ctm.GetFloatArray(CTM_VERTICES);
    CTMuint triCount = ctm.GetInteger(CTM_TRIANGLE_COUNT);
    const CTMuint *indices = ctm.GetIntegerArray(CTM_INDICES);

    vtkSmartPointer<vtkPolyData> newPd = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> newCells = vtkSmartPointer<vtkCellArray>::New();

    for( CTMuint i = 0; i < vertCount; ++i )
    {
        Point pt;
        for( int j = 0; j < 3; ++j )
        {
            pt[j] = vertices[3*i+j];
        }
        newPoints->InsertNextPoint( pt.point );
    }
    for( CTMuint i = 0; i < triCount; ++i )
    {
        vtkIdType cell[3];
        for( int j = 0; j < 3; ++j )
        {
            cell[j] = indices[3*i+j];
        }
        newCells->InsertNextCell( 3, cell );
    }
    newPd->SetPoints( newPoints );
    newPd->SetPolys( newCells );
    newPd->Modified();

    m_Data->DeepCopy( newPd );
}

void ctmIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    vtkPoints *points = data->GetPoints();
    CTMuint aVertCount = static_cast<unsigned int>( points->GetNumberOfPoints() );
    CTMfloat *aVertices = new CTMfloat[3*aVertCount];
    for( CTMuint i = 0; i < aVertCount; ++i )
    {
        Point pt( points->GetPoint( i ) );
        for( CTMuint j = 0; j < 3; ++j )
        {
            aVertices[3*i+j] = static_cast<CTMfloat>( pt[j] );
        }
    }
    CTMuint aTriCount = static_cast<CTMuint>( data->GetNumberOfCells() );
    CTMuint *aIndices = new CTMuint[3*aTriCount];
    for( CTMuint i = 0; i < aTriCount; ++i )
    {
        vtkIdList *ids = data->GetCell( i )->GetPointIds();
        for( CTMuint j = 0; j < 3; ++j )
        {
            aIndices[3*i+j] = static_cast<CTMuint>( ids->GetId( j ) );
        }
    }

    SaveFile( aVertCount, aTriCount, aVertices, aIndices, filePath.c_str(), nullptr, nullptr );

    delete [] aVertices;
    aVertices = nullptr;
    delete [] aIndices;
    aIndices = nullptr;
}

void ctmIO::SaveFile(CTMuint aVertCount, CTMuint aTriCount,
                     CTMfloat *aVertices, CTMuint *aIndices,
                     const char *aFileName,
                     const CTMfloat *aAttribValues, const char *aName)
{
    try
    {
        // Create a new OpenCTM exporter object
        CTMexporter ctm;

        // Define our mesh representation to OpenCTM (store references to it in
        // the context)
        ctm.DefineMesh(aVertices, aVertCount, aIndices, aTriCount, NULL);

        // Save the OpenCTM file
        ctm.Save(aFileName);
    }
    catch(exception &e)
    {
        fprintf( stderr, "[%s, %d]: Error => %s\n", __FILE__, __LINE__, e.what( ) );
    }
}
