#include <iostream>
#include <string>

#include "ULog.h"
#include "stlIO.h"
#include "objIO.h"
using namespace std;

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
    if( old_suffix == "stl" )
    {
        reader = new stlIO();
    }

    if( new_suffix == "obj" )
    {
        writer = new objIO();
    }

    if( reader && writer )
    {
        reader->Read( file_name );
        data = reader->GetData();
        std::string baseName = reader->GetBaseName( file_name );
        std::string newFilePath = baseName + "." + new_suffix;
        writer->Write( (vtkPolyData*)data, newFilePath );

        delete reader;
        reader = nullptr;
        delete writer;
        writer = nullptr;
    }
    return 0;
}
