/**********************************************************
*
* @brief    The details for class WindowGrabber which is
*           responsible to grab Gif window.
*
* @author   theArcticOcean
***********************************************************/

#include "windowgrabber.h"

#include <QPixmap>
#include <QDir>
#include <QtDebug>
#include <QGuiApplication>
#include <QWindow>
#include <dirent.h>
#include <QFileDialog>
#include <QMessageBox>
#include <errno.h>
#include <QRegularExpression>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

WindowGrabber* WindowGrabber::instance = NULL;

/*
*   Constructor of WindowGrabber.
*   Make sure images folder exist.
*   Setting for signal-slot mechanism for WindowGrabber and ImagesCombiner.
*/
WindowGrabber::WindowGrabber()
    : rectX( 0 )
    , rectY( 0 )
    , rectWidth( -1 )
    , rectHeight( -1 )
    , p_imageCombiner( ImagesCombiner::getInstance() )
{

    imageFolderPath = QCoreApplication::applicationDirPath();
    imageFolderPath = imageFolderPath + "/Pictures";

    if( access( imageFolderPath.toStdString().c_str(), F_OK ) )
    {
        qDebug() << imageFolderPath + " doesn't exist.";
#ifdef Q_OS_WIN
        if( mkdir( imageFolderPath.toStdString().c_str() ) )
#else
        if( mkdir( imageFolderPath.toStdString().c_str(), 0755 ) )
#endif
        {
            qCritical() << "mkdir failed for "<< imageFolderPath << " "<< strerror(errno);
        }
    }

    qDebug() << "imageFolderPath: " << imageFolderPath;
    grabTimer.setInterval( 40 );

    connect( &grabTimer, &QTimer::timeout, this, &WindowGrabber::grabWindow );
    connect( p_imageCombiner, &ImagesCombiner::combineImagesFinished, this, &WindowGrabber::saveGif );

    p_imageCombiner->setIsRuning( true );
    p_imageCombiner->start();
}

/*
*   Provide WindowGrabber object pointer to the outside for some scenes.
*   such as connect function and qmlRegisterSingletonType callback function.
*/
WindowGrabber *WindowGrabber::getInstance()
{
    if( NULL == instance )
    {
        instance = new WindowGrabber();
    }
    return instance;
}

/*
*   After the software exits, we need to make sure system child process is not running and clear
*   various grab screen images generated temporarily.
*/
WindowGrabber::~WindowGrabber()
{
    if( NULL != p_imageCombiner )
    {
        // p_imageCombiner->exit( 0 );  // Doesn't works.
        p_imageCombiner->terminateSystemChildProcess();
        p_imageCombiner->setIsRuning( false );
        // Let it runs continuely, don't block because of semaphore
        p_imageCombiner->releaseSemaphore();


        qDebug() << "start to delete p_imageCombiner";
        p_imageCombiner->wait( 200 );   // milliseconds
        delete p_imageCombiner;
        p_imageCombiner = NULL;
    }
    clearImagesFolder();
}

/*
*   The function is called in QML file.
*   It sets record live area and notifies WindowGrabber to start to grab screen.
*/
void WindowGrabber::startGrab( const double &x, const double &y, const double &w, const double &h)
{
    rectX = static_cast<int>( x + 0.5 );
    rectY = static_cast<int>( y + 0.5 );
    rectWidth = static_cast<int>( w + 0.5 );
    rectHeight = static_cast<int>( h + 0.5 );

    imageCount = 0;
    grabTimer.start();
}

/*
*   Slot function for WaitWindowAnimation::stopGrab
*/
void WindowGrabber::onStopGrab()
{
    grabTimer.stop();
}

/*
*   Set frame rate to combine images to generate gif file.
*/
void WindowGrabber::setFramePerSec(const int rate)
{
    framePerSec = rate;
    qDebug() << " rate is " << rate;
}

/*
*   Create cmd string for system.
*   Notify ImagesCombiner to work.
*/
void WindowGrabber::combineImages()
{
    // simple example command: ffmpeg -threads 1 -y -r 24 -i ./out%d.png -final_delay 300 output.gif
    QString tmp;
    QString cmdStr;
#ifdef Q_OS_WIN
    cmdStr = "C:\\Program Files\\ffmpeg\\bin\\ffmpeg -threads 1 -y ";
#else
    cmdStr = "ffmpeg -threads 1 -y ";
#endif
    cmdStr = cmdStr + "-r ";
    cmdStr = cmdStr + QString::number(framePerSec);
    cmdStr = cmdStr + " ";
    cmdStr = cmdStr + "-i ";
    cmdStr = cmdStr + imageFolderPath;
    cmdStr = cmdStr + "/out%d.png ";
    cmdStr = cmdStr + "-final_delay 300 ";
    cmdStr = cmdStr + imageFolderPath;
    cmdStr = cmdStr + "/output.gif";

    p_imageCombiner->copyCmdStr( cmdStr );
    p_imageCombiner->releaseSemaphore();
}

/*
*   Slot function grabWindow is connect with grabTimer::timeout()
*/
void WindowGrabber::grabWindow()
{
    QScreen *p_screenTmp = QGuiApplication::primaryScreen();
    if ( const QWindow *window = windowHandle() )
    {
        qDebug() << "window->screen()";
        p_screenTmp = window->screen();
    }
    if ( !p_screenTmp )
        return ;

    // same as Gif window's info
    // qDebug() << QString("(%1, %2, %3, %4)").arg(rectX).arg(rectY).arg(rectWidth).arg(rectHeight);
    // (1440, 900). Main window in qml has size (1440, 823).
    // qDebug() << QString("(%1, %2)").arg(p_screenTmp->geometry().width()).arg(p_screenTmp->geometry().height());

    // offset values are used to avoid to copy Gif red border line.
    int offY = 1;
    int offX = 1;
    int offW = -1;
    int offH = -1;
    QPixmap map = p_screenTmp->grabWindow( 0, rectX + offX, rectY + offY, rectWidth + 3*offW, rectHeight + 3*offH );
    QString fileName = imageFolderPath + "/out";
    fileName = fileName + QString::number( ++imageCount );
    fileName = fileName + ".png";
    if( !map.save( fileName, 0, 100 ) )
    {
        qCritical() << "save " + fileName << " failed !!!";
    }
}

/*
*   Show "save as" window, the default path is user home path.
*/
void WindowGrabber::saveGif()
{
    if( p_imageCombiner->getCombineResult() )
    {
inputPath:
        QFileDialog dialog;
        QString path;
        QString defaultPath = QDir::homePath();
        defaultPath = defaultPath + "/out.gif";

#ifdef Q_OS_OSX
        dialog.setWindowIcon(QIcon(":/Images/logo.icns"));
#else
        dialog.setWindowIcon(QIcon(":/Images/logo.ico"));
#endif
        path = dialog.getSaveFileName( this,
                                       "save file",
                                       defaultPath,
                                       tr("Images (*.gif)")
                                       );
        if( !path.isEmpty() ){
            QString oldPath = imageFolderPath + "/output.gif";
#ifdef Q_OS_WIN
            if( 0 == access( path.toStdString().c_str(), F_OK ) )
            {
                if( -1 == unlink( path.toStdString().c_str() ) )
                {
                    qCritical() << "unlink " << path << "failed: " << strerror(errno);
                }
                else
                {
                    qDebug() << "unlink " << path << "successfully.";
                }
            }
#endif
            if( -1 == rename( oldPath.toStdString().c_str(), path.toStdString().c_str() ) )
            {
                QString tmp = "rename failed ";
                tmp = tmp + strerror(errno);
                tmp = tmp + ", oldPath: ";
                tmp = tmp + oldPath;

                qWarning() << tmp;
                QMessageBox::critical( this,
                                       tr("Rename Failed"),
                                       tmp,
                                       QMessageBox::Ok
                                       );
            }
            else {
                qDebug() << "generate gif file: " << path;
                clearImagesFolder();
            }
        }
        else
        {
            QMessageBox::critical( this,
                                   tr("Empty path"),
                                   tr("Please enter path to store gif file."),
                                   QMessageBox::Ok
                                   );
            goto inputPath;
        }
    }
    else
    {
        QMessageBox::critical( this,
                               tr("Combine Images Error"),
                               tr("There is error when combine images.\nPlease read log.txt to fix bug."),
                               QMessageBox::Ok
                               );
    }
}

/*
*   Delete all files in images folder.
*/
void WindowGrabber::clearImagesFolder()
{
    DIR *dir;
    struct dirent * ptr;
    int filesCount;

    filesCount = 0;
    dir = opendir( imageFolderPath.toStdString().c_str() );
    if( NULL == dir )
    {
        qCritical() << "opendir for imageFolderPath failed " << strerror(errno);
        return ;
    }

    while( ( ptr = readdir(dir) ) != NULL )
    {
        if( strcmp( ptr->d_name, ".") == 0 || strcmp( ptr->d_name, ".." ) == 0 )
        {
            continue;
        }

        QString filePath = imageFolderPath;
        filePath = filePath + "/";
        filePath = filePath + ptr->d_name;

        if( -1 == unlink( filePath.toStdString().c_str() ) )
        {
            QString info = "unlink ";
            info = info + ptr->d_name;
            info = info + " failed ";
            qCritical() << info << " " << strerror(errno);
        }
        else
        {
            ++filesCount;
        }
    }
    qDebug() << "unlink " << filesCount << "files in " << imageFolderPath;
}
