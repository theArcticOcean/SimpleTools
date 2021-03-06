#include <iostream>
#include <string>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#include "ULog.h"
#include "stlIO.h"
#include "objIO.h"
#include "plyIO.h"
#include "vtpIO.h"
#include "vtkIO.h"
#include "gltfIO.h"
#include "facetIO.h"
#include "filesManager.h"
#include "ctmIO.h"
#include "byuIO.h"
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
            std::cout << "read file failed" << endl;
            return -1;
        }

        data = reader->GetData();

        std::string baseName = filesManager::GetInstance()->GetBaseName( file_name );
        std::string newFilePath = baseName + "." + new_suffix;
        newFilePath = writer->Write( (vtkPolyData*)data, newFilePath );

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
    else if( old_suffix == "gltf" )
    {
        reader = new gltfIO();
    }
    else if( old_suffix == "facet" )
    {
        reader = new facetIO();
    }
    else if( old_suffix == "ctm" )
    {
        reader = new ctmIO();
    }
    else if( old_suffix == "byu" )
    {
        reader = new byuIO();
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
    else if( new_suffix == "gltf" )
    {
        writer = new gltfIO();
    }
    else if( new_suffix == "facet" )
    {
        writer = new facetIO();
    }
    else if( new_suffix == "ctm" )
    {
        writer = new ctmIO();
    }
    else if( new_suffix == "byu" )
    {
        writer = new byuIO();
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
