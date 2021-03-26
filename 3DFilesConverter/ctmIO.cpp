#include "ctmIO.h"
#include "point.hpp"
#include "ULog.h"
#include "filesManager.h"

#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <unistd.h>

ctmIO::ctmIO()
{

}

ctmIO::~ctmIO()
{

}

bool ctmIO::Read(std::string filePath)
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

    /* try {
        const CTMfloat *scalars1 = ctm.GetFloatArray( CTM_ATTRIB_MAP_1 );
        Log( IInfo, "length: ", sizeof (scalars1) / sizeof (scalars1[0]) );
        vtkSmartPointer<vtkDoubleArray> ptScalars = vtkSmartPointer<vtkDoubleArray>::New();
        for( CTMuint i = 0; i < vertCount; ++i )
        {
            ptScalars->InsertNextTuple1( scalars1[4*i] );
        }

        newPd->GetPointData()->SetScalars( ptScalars );
    }
    catch ( ctm_error ctmErr ) {
        Log( IWarning, "No point scalar" );
    }

    try {
        const CTMfloat *scalars2 = ctm.GetFloatArray( CTM_ATTRIB_MAP_2 );
        vtkSmartPointer<vtkDoubleArray> cellScalars = vtkSmartPointer<vtkDoubleArray>::New();
        for ( CTMuint i = 0; i < triCount; ++i )
        {
            cellScalars->InsertNextTuple1( scalars2[4*i] );
        }
        newPd->GetCellData()->SetScalars( cellScalars );
    }
    catch ( ctm_error ctmErr ) {
        Log( IWarning, "No cell scalar" );
    } */

    newPd->Modified();

    m_Data->DeepCopy( newPd );

    return true;
}

std::string ctmIO::Write(vtkSmartPointer<vtkPolyData> data, std::string filePath)
{
    if ( access( filePath.c_str(), F_OK ) == 0 )
    {
        Log( IInfo, "start to remove exist file" );
        filesManager::GetInstance()->RemoveDir( filePath.c_str() );
    }

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

    /*CTMfloat *ptScalars = new CTMfloat[aVertCount*4];
    if( data->GetPointData() && data->GetPointData()->GetScalars() )
    {
        auto scalars = data->GetPointData()->GetScalars();
        for( CTMuint i = 0; i < aVertCount; ++i )
        {
            ptScalars[i*4] = scalars->GetTuple1( i );
        }
    }
    else {
        for( CTMuint i = 0; i < aVertCount; ++i )
        {
            ptScalars[i*4] = 1;
        }
    }

    CTMfloat *cellScalars = new CTMfloat[aTriCount*4];
    if( data->GetCellData() && data->GetCellData()->GetScalars() )
    {
        auto scalars = data->GetCellData()->GetScalars();
        for( CTMuint i = 0; i < aTriCount; ++i )
        {
            cellScalars[i*4] = scalars->GetTuple1( i );
        }
    }
    else {
        for( CTMuint i = 0; i < aTriCount; ++i )
        {
            cellScalars[i*4] = 1;
        }
    } */

    SaveFile( aVertCount, aTriCount, aVertices, aIndices, filePath.c_str(),
              nullptr, nullptr,   //ptScalars, "ptScalars",
              nullptr, nullptr ); //cellScalars, "cellScalars" );

    delete [] aVertices;
    aVertices = nullptr;
    delete [] aIndices;
    aIndices = nullptr;
    /*delete [] ptScalars;
    ptScalars = nullptr;
    delete [] cellScalars;
    cellScalars = nullptr;*/

    return filePath;
}

void ctmIO::SaveFile(CTMuint aVertCount, CTMuint aTriCount,
                     CTMfloat *aVertices, CTMuint *aIndices,
                     const char *aFileName,
                     const CTMfloat *aAttribValues0, const char *aName0,
                     const CTMfloat *aAttribValues1, const char *aName1)
{
    try
    {
        // Create a new OpenCTM exporter object
        CTMexporter ctm;

        // Define our mesh representation to OpenCTM (store references to it in
        // the context)
        ctm.DefineMesh(aVertices, aVertCount, aIndices, aTriCount, NULL);

        if( aAttribValues0 ) {
            ctm.AddAttribMap( aAttribValues0, aName0 );
        }
        if( aAttribValues1 ) {
            ctm.AddAttribMap( aAttribValues1, aName1 );
        }

        // Save the OpenCTM file
        ctm.Save(aFileName);
    }
    catch(exception &e)
    {
        fprintf( stderr, "[%s, %d]: Error => %s\n", __FILE__, __LINE__, e.what( ) );
    }
}
