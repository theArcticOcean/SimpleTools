#include "logprinter.h"

/*
*   Create log file, truncate the file if it exsits.
*/
void LogInit()
{
    logFilePath = QCoreApplication::applicationDirPath();
    logFilePath = logFilePath + "/log.txt";
    if(  0 == access( logFilePath.toStdString().c_str(), F_OK )
         && truncate( logFilePath.toStdString().c_str(), 0 ) )
    {
        QString prefix = "[logInit] ";
        prefix = prefix + logFilePath;
        perror( prefix.toStdString().c_str() );
    }
}

void print(const char *file, const int line, const char *fmt, ...)
{
    const int BUFFSIZE = 1024;
    char buffer[ BUFFSIZE ] = {0};
    int offset = 0;
    FILE *fp = NULL;

    offset = snprintf( buffer + offset, BUFFSIZE - offset, "[%s, %d]\n", file, line );

    va_list vap;
    va_start( vap, fmt );  //variable arguments list vap init
    vsnprintf( buffer + offset, BUFFSIZE - offset, fmt, vap ); // add list vap to buff
    va_end( vap );

    offset = strlen( buffer );
    offset = snprintf( buffer + offset, BUFFSIZE - offset, "\n" );

    fp = fopen( logFilePath.toStdString().c_str(), "a" );
    if( NULL != fp )
    {
        fprintf( fp, "%s", buffer );
        fclose( fp );
    }
}
