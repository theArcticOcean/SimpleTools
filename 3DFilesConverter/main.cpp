#include <iostream>
#include <string>

#include "ULog.h"
#include "stlIO.h"
#include "objIO.h"
using namespace std;

void ChooseReader( IOBase *&reader, std::string old_suffix );
void ChooseWriter( IOBase *&writer, std::string new_suffix );

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
        reader->Read( file_name );
        data = reader->GetData();
        std::string baseName = reader->GetBaseName( file_name );
        std::string newFilePath = baseName + "." + new_suffix;
        writer->Write( (vtkPolyData*)data, newFilePath );
        Log( IInfo, newFilePath );

        delete reader;
        reader = nullptr;
        delete writer;
        writer = nullptr;
    }
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
}
