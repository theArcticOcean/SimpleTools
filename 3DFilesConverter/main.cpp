#include <iostream>
#include <string>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <sys/stat.h>
#include <stdio.h>

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

#include "ULog.h"
#include "stlIO.h"
#include "objIO.h"
#include "plyIO.h"
#include "vtpIO.h"
#include "vtkIO.h"
#include "facetIO.h"
#include "filesManager.h"
#include "ctmIO.h"
#include "demIO.h"
#include "tiffIO.h"
#include "3DSIO.h"
#include "x3dIO.h"
#include "wrlIO.h"
using namespace std;

void ChooseReader( IOBase *&reader, std::string old_suffix );
void ChooseWriter( IOBase *&writer, std::string new_suffix );
void FreePointer( IOBase *&ptr );

// parameters: exe_path file_name old_suffix new_suffix.
int main( int argc, char **argv )
{
    if( argc < 4 )
    {
        fprintf( stderr, "please use command format: exe_path file_name old_suffix new_suffix.\n" );
        return -1;
    }
    string file_name( argv[1] );
    string old_suffix( argv[2] );
    string new_suffix( argv[3] );
    Log( IInfo, file_name, ", ", old_suffix, ", ", new_suffix );
    IOBase *reader = nullptr;
    IOBase *writer = nullptr;
    vtkDataObject *data = nullptr;
    ChooseReader( reader, old_suffix );
    ChooseWriter( writer, new_suffix );
    Log( IInfo, reader, ", ", writer );

    if( reader && writer )
    {
        std::string folder;
        if( !reader->Read( file_name ) )
        {
            Log( IError, "read filed: ", old_suffix );
            std::cout << INVALID_FILE << endl;
            return -1;
        }

        data = reader->GetData();

        std::string baseName = filesManager::GetInstance()->GetBaseName( file_name );
        std::string newFilePath = baseName + "." + new_suffix;
        newFilePath = writer->Write( (vtkPolyData*)data, newFilePath );
        if( newFilePath.length() < 1 )
        {
            Log( IError, "write failed: ", newFilePath );
            std::cout << INVALID_FILE << endl;
            return -1;
        }

        Log( IInfo, newFilePath );
        std::cout << newFilePath << std::endl;
    }

    FreePointer( reader );
    FreePointer( writer );
    return 0;
}


void ChooseReader( IOBase *&reader, std::string old_suffix )
{
    if( old_suffix == "stl" )
    {
        reader = new stlIO();
    }
    else if( old_suffix == "obj" )
    {
        reader = new objIO();
    }
    else if( old_suffix == "ply" )
    {
        reader = new plyIO();
    }
    else if( old_suffix == "vtp" )
    {
        reader = new vtpIO();
    }
    else if( old_suffix == "vtk" )
    {
        reader = new vtkIO();
    }
    else if( old_suffix == "facet" )
    {
        reader = new facetIO();
    }
    else if( old_suffix == "ctm" )
    {
        reader = new ctmIO();
    }
    else if( old_suffix == "dem" )
    {
        reader = new demIO();
    }
    else if( old_suffix == "tif" )
    {
        reader = new tiffIO();
    }
    else if( old_suffix == "3ds" )
    {
        reader = new w3DSIO();
    }
}

void ChooseWriter( IOBase *&writer, std::string new_suffix )
{
    if( new_suffix == "stl" )
    {
        writer = new stlIO();
    }
    else if( new_suffix == "obj" )
    {
        writer = new objIO();
    }
    else if( new_suffix == "ply" )
    {
        writer = new plyIO();
    }
    else if( new_suffix == "vtp" )
    {
        writer = new vtpIO();
    }
    else if( new_suffix == "vtk" )
    {
        writer = new vtkIO();
    }
    else if( new_suffix == "facet" )
    {
        writer = new facetIO();
    }
    else if( new_suffix == "ctm" )
    {
        writer = new ctmIO();
    }
    else if( new_suffix == "dem" )
    {
        writer = new demIO();
    }
    else if( new_suffix == "tif" )
    {
        writer = new tiffIO();
    }
    else if( new_suffix == "3ds" )
    {
        writer = new w3DSIO();
    }
    else if( new_suffix == "x3d" )
    {
        writer = new x3dIO();
    }
    else if( new_suffix == "wrl" )
    {
        writer = new wrlIO();
    }
}

void FreePointer( IOBase *&ptr )
{
    if( nullptr != ptr )
    {
        delete ptr;
        ptr = nullptr;
    }
}
