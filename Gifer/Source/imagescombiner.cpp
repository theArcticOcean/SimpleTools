/**********************************************************
*
* @brief    The details of generating gif file in class
*           ImagesCombiner
*
* @author   theArcticOcean
***********************************************************/

#include "imagescombiner.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#ifdef Q_OS_LINUX
	#include <sys/types.h>
	#include <sys/wait.h>
#endif

ImagesCombiner* ImagesCombiner::instance = NULL;

/*
*   Constructor of ImagesCombiner.
*/
ImagesCombiner::ImagesCombiner()
    : cmdStr( QString("") )
    , combineResult( false )
    , isRunning( false )
{
    setTerminationEnabled( true );
}

/*
*   When Gifer exists, we make child process created by system2 function also exist.
*   It avoids that various child processes live in the background.
*/
ImagesCombiner::~ImagesCombiner()
{

}

/*
*   Rewrite libc system function to make cmdString running and store child
*   process id. So we can kill child process if it exists but software exits.
*/
int ImagesCombiner::system2(const char *cmdstring)
{   
    int status;

    cmdPid = 0;

#ifdef Q_OS_WIN
    if( NULL == cmdstring )
    {
        qWarning() << "cmdstring is NULL";
        return -1;
    }
    STARTUPINFO stStartUpInfo;
    memset(&stStartUpInfo, 0 ,sizeof(stStartUpInfo));
    stStartUpInfo.cb = sizeof(stStartUpInfo);

    PROCESS_INFORMATION stProcessInfo;
    memset(&stProcessInfo, 0 ,sizeof(stProcessInfo));

    WCHAR *szPath = NULL;
    WCHAR *szCmd = charToWchar( cmdstring );

    bool bRet = ::CreateProcess(
        szPath,
        szCmd,
        NULL,
        NULL,
        false,
        NULL,
        NULL,
        NULL,
        &stStartUpInfo,
        &stProcessInfo);
    if( bRet )
    {
        cmdPid = stProcessInfo.dwProcessId;
        if( WaitForProcessExit() )
        {
            status = 0;
        }
        else
        {
            status = -1;
        }
    }
    else
    {
        LPVOID msg;
        FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       GetLastError(),
                       MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                       (LPSTR)&msg,
                       0,
                       NULL );
        qCritical() << "CreateProcess: " << (LPTSTR)msg;
        LocalFree( msg );
        status = -1;
    }
#else
    pid_t pid;

    if( cmdstring == NULL )
    {
        return 1;
    }

    if( ( pid = fork() ) < 0 )
    {
        status = -1;
    }
    else if( pid == 0 )
    {
        // execl create new process to replace old process
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        // if above statement execute successfully, the following function would not work.
        _exit(127);
    }
    else
    {
        cmdPid = pid;
        // For waitpid return value, -1 means error, 0 means no exited child.
        // Positive interger means child PID.
        while( waitpid(pid, &status, 0) < 0 )
        {
            // EINTR means interrupt signal, operate failed. Please try again.
            if( errno != EINTR )
            {
                status = -1;
                break;
            }
        }
    }
    cmdPid = 0;
#endif
    return status;
}

#ifdef Q_OS_WIN
bool ImagesCombiner::WaitForProcessExit()
{
    int ret = false;
    HANDLE handle = ::OpenProcess( PROCESS_ALL_ACCESS, 0, cmdPid );
    if ( handle )
    {
        DWORD tmpWord = ::WaitForSingleObject(handle, INFINITE);
        while( WAIT_OBJECT_0 != tmpWord )
        {
            LPVOID msg;
            FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           GetLastError(),
                           MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                           (LPSTR)&msg,
                           0,
                           NULL );
            qCritical() << "WaitForSingleObject: " << (LPTSTR)msg;
            LocalFree( msg );

            if( WAIT_FAILED == tmpWord )
            {
                break;
            }
        }
        ret = true;
    }
    return ret;
}

WCHAR *ImagesCombiner::charToWchar( const char *s )
{
    int w_nlen = MultiByteToWideChar( CP_ACP, 0, s, -1, NULL, 0 );
    if( 0 == w_nlen )
    {
        LPVOID msg;
        FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       GetLastError(),
                       MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                       (LPSTR)&msg,
                       0,
                       NULL );
        qCritical() << "MultiByteToWideChar: " << (LPTSTR)msg;
        LocalFree( msg );
        return NULL;
    }
    WCHAR *wStr;
    wStr = ( WCHAR* )malloc( sizeof(WCHAR) * w_nlen );
    memset( wStr, 0, sizeof(WCHAR) * w_nlen );
    w_nlen = MultiByteToWideChar( CP_ACP, 0, s, -1, wStr, w_nlen );
    qDebug() << "MultiByteToWideChar return: " << w_nlen;
    if( 0 == w_nlen )
    {
        LPVOID msg;
        FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       GetLastError(),
                       MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                       (LPSTR)&msg,
                       0,
                       NULL );
        qCritical() << "MultiByteToWideChar: " << (LPTSTR)msg;
        LocalFree( msg );
        return NULL;
    }
    return wStr;
}
#endif

/*
*   Provide ImagesCombiner object pointer to the outside for some scenes
*   such as connect function paramter.
*/
ImagesCombiner *ImagesCombiner::getInstance()
{
    if( NULL == instance )
    {
        instance = new ImagesCombiner();
    }
    return instance;
}

/*
*   This function is provided for WindowGrabber.
*   When WindowGrabber calls it, ImagesCombiner's independent thread do its task.
*/
void ImagesCombiner::releaseSemaphore()
{
    sem.release(1);
}

/*
*   This function is provided for WindowGrabber.
*   Assign string to cmdStr, then ImagesCombiner would execute the command.
*/
void ImagesCombiner::copyCmdStr(const QString _cmdStr)
{
    cmdStr = _cmdStr;
}

/*
*   Get result of generating gif file.
*/
bool ImagesCombiner::getCombineResult()
{
    return combineResult;
}

void ImagesCombiner::setIsRuning(const bool _isRunning)
{
    isRunning = _isRunning;
}

void ImagesCombiner::terminateSystemChildProcess()
{
    qDebug( "child pid for system function is %d", cmdPid );
    if( cmdPid > 0 )
    {
#ifdef Q_OS_WIN
        HANDLE  hProcess;
        UINT    uExitCode;
        LPVOID  msg;

        hProcess = OpenProcess( PROCESS_TERMINATE, FALSE, cmdPid );
        if( NULL == hProcess )
        {
            FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                          NULL,
                          GetLastError(),
                          MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                          (LPSTR)&msg,
                          0,
                          NULL);
            qCritical() << "OpenProcess: " << (LPTSTR)msg;
            LocalFree( msg );
            return ;
        }

        if( !TerminateProcess( hProcess, uExitCode ) )
        {
            FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           GetLastError(),
                           MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                           (LPSTR)&msg,
                           0,
                           NULL );
            qCritical() << "Terminate process: " << (LPTSTR)msg;
            LocalFree( msg );
        }
        else
        {
            qDebug() << "TerminateProcess " << cmdPid << " successfully.";
        }
    }
#else
        if ( -1 == kill( cmdPid, SIGKILL ) )
        {
            qCritical() << "kill child process failed: " << strerror(errno);
        }
        else
        {
            qInfo() << "kill child process " << cmdPid;
        }
    }
#endif
}

/*
*   The job details of ImagesCombiner's independent thread.
*   After waiting window shows, it starts to work.
*/
void ImagesCombiner::run()
{
    while(1)
    {
        sem.acquire(1);
        if( false == isRunning )
        {
            qDebug() << "isRunning is false, current thread exits.";
            break;
        }
        int ret;

        combineResult = false;
        ret = system2( cmdStr.toStdString().c_str() );

        qDebug() << "cmdStr: " << cmdStr;

#ifdef Q_OS_WIN
        if( -1 == ret )
        {
            qCritical() << "system2 execute failed.";
        }
        else
        {
            combineResult = true;
        }
#else
        // create sub process
        if (-1 == ret)
        {
            qCritical("system error!");
        }
        else
        {
            qDebug("ret is not -1, exit ret value = [0x%x]", ret);  //0x7f00

            // call shell script and finish successfully.
            if (WIFEXITED(ret))   // WIFEXITED is a macro
            {
                if (0 == WEXITSTATUS(ret))  // return value of shell script run.
                {
                    qDebug("run shell script successfully.");
                    combineResult = true;
                }
                // 0x7f = 127
                else
                {
                    qCritical("run shell script fail, script exit code: %d, reason: %s", WEXITSTATUS(ret), strerror(errno));
                }
            }
            else
            {
                qCritical("exit ret = [%d]", WEXITSTATUS(ret));
            }
        }
#endif
        qInfo() << "combineImagesFinished.";
        emit combineImagesFinished();
    }
}
