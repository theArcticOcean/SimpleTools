/**********************************************************
*
* @brief    Class ImagesCombiner is used to combine all images
*           to generate gif file.
*
* @author   theArcticOcean
***********************************************************/

#ifndef IMAGESCOMBINER_H
#define IMAGESCOMBINER_H

#include <QSemaphore>
#include <QThread>
#include <QDebug>
#ifdef Q_OS_WIN
    #include <windows.h>
    #include <wchar.h>
#endif

class ImagesCombiner : public QThread
{
    Q_OBJECT
public:
    static ImagesCombiner* getInstance();
    ~ImagesCombiner();
    void releaseSemaphore();
    void copyCmdStr(const QString _cmdStr);
    bool getCombineResult();
    void setIsRuning( const bool _isRunning);
    void terminateSystemChildProcess();

protected:
    void run();

signals:
    void combineImagesFinished();

private:
    ImagesCombiner();
    int system2( const char * cmdstring);
#ifdef Q_OS_WIN
    bool WaitForProcessExit();
    WCHAR * charToWchar( const char *s );
#endif

    QSemaphore sem;
    QString cmdStr;
    bool combineResult;
    static ImagesCombiner* instance;
    int cmdPid;
    bool isRunning;
};

#endif // IMAGESCOMBINER_H
