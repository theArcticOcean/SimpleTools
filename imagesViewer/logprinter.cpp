#include "logprinter.h"

/*
*   Create log file, truncate the file if it exsits.
*/
void ImagesViewer::LogInit()
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

/*
*   The function is provided for qInstallMessageHandler.
*   It redirects output messages to log file.
*/
void ImagesViewer::LogBase(
    QtMsgType type,
    const QMessageLogContext &context,
    const QString &msg
    )
{
    FILE *fp;
    int offset;
    char buffer[ BUFFER_SIZE ] = {0};
    QByteArray localMsg = msg.toLocal8Bit();

    fp = NULL;
    switch( type )
    {
    case QtDebugMsg:
    offset = sprintf( buffer, "[Debug ");
    break;
    case QtInfoMsg:
    offset = sprintf( buffer, "[Info ");
    break;
    case QtWarningMsg:
    offset = sprintf( buffer, "[Warning " );
    break;
    case QtCriticalMsg:
    offset = sprintf( buffer, "[Critical " );
    break;
    case QtFatalMsg:
    offset = sprintf( buffer, "[Fatal " );
    break;
    }

    sprintf( buffer + offset, "(%s, %u, %s)]\n%s\n\n", context.file, context.line, context.function, localMsg.constData() );
#if DEBUG_SLIENCE
    fp = fopen( logFilePath.toStdString().c_str(), "a" );
    if( NULL != fp )
    {
        fprintf( fp, "%s", buffer );
        fclose( fp );
    }
#else
    printf( "%s", buffer );
#endif
}

/*
*   The function is provided for user to replace printf.
*/
void ImagesViewer::print(const char *file, const int line, const char *func,const char *fmt, ...)
{
    char buffer[ BUFFER_SIZE ] = {0};
    int offset = 0;
    FILE *fp = NULL;

    offset = snprintf( buffer + offset, BUFFER_SIZE - offset, "[%s, %d, %s]\n", file, line, func );

    va_list vap;
    va_start( vap, fmt );  //variable arguments list vap init
    vsnprintf( buffer + offset, BUFFER_SIZE - offset, fmt, vap ); // add list vap to buff
    va_end( vap );

    offset = strlen( buffer );
    offset = snprintf( buffer + offset, BUFFER_SIZE - offset, "\n" );
#if DEBUG_SLIENCE
    fp = fopen( logFilePath.toStdString().c_str(), "a" );
    if( NULL != fp )
    {
        fprintf( fp, "%s", buffer );
        fclose( fp );
    }
#else
   printf( "%s", buffer );
#endif
}
