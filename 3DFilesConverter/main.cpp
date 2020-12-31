#include <iostream>
#include <string>

#include "ULog.h"
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
    return 0;
}
