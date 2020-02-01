/**********************************************************
*
* @brief    The definition details of class WaitWindowAnimation.
*
* @author   theArcticOcean
***********************************************************/

#include "waitwindowanimation.h"
#include "windowgrabber.h"

#include <QQmlContext>
#include <QThread>
#include <QMatrix>

WaitWindowAnimation* WaitWindowAnimation::instance = NULL;

/*
*   Constructor of WaitWindowAnimation.
*   It loads waitWindow.qml and configure signal and slot for ImagesCombiner and WindowGrabber.
*/
WaitWindowAnimation::WaitWindowAnimation(QQmlEngine *engine, QObject *parent)
    : QObject( parent )
    , p_imgProvider( new WaitImageProvider )
    , p_qmlEngine( engine )
    , p_waitWinComponent( NULL )
    , p_mainWindow( NULL )
    , p_image( NULL )
    , p_waitWinQuickItem( NULL )
    , p_timer(new QTimer)
    , p_revolveTimer( new QTimer )
    , revolveIndex( 0 )
    , clicked( false )
{
    p_waitWinComponent = new QQmlComponent( p_qmlEngine );

    //Asynchronous load method makes Load/compile the component in a background thread.
    p_waitWinComponent->loadUrl( QUrl("qrc:/Qml/waitWindow.qml"), QQmlComponent::Asynchronous );

    if( p_waitWinComponent->status() != QQmlComponent::Ready )
    {
        connect( p_waitWinComponent, &QQmlComponent::statusChanged,
                 this, &WaitWindowAnimation::finishCreateWaitWindow );
    }
    else
    {
        finishCreateWaitWindow();
    }
    connect( p_timer, &QTimer::timeout, this, &WaitWindowAnimation::combineImagesTrigger );
    connect( ImagesCombiner::getInstance(), &ImagesCombiner::combineImagesFinished, this, &WaitWindowAnimation::hide );
    connect( this, &WaitWindowAnimation::stopGrab, WindowGrabber::getInstance(), &WindowGrabber::onStopGrab );
}

/*
*   Make wait window visible and stop grab screen area.
*   After short time, combine images to generate gif file.
*/
bool WaitWindowAnimation::show()
{
    if( NULL != p_mainWindow && NULL != p_waitWinQuickItem )
    {
        emit stopGrab();
        QQuickItem *p_contentItem = p_mainWindow->contentItem();
        qDebug() << p_waitWinQuickItem << " "<< p_contentItem;
        p_waitWinQuickItem->setParentItem( p_contentItem );
        p_waitWinQuickItem->setParent( p_qmlEngine );
        p_waitWinQuickItem->setVisible( true );
        // p_waitWinQuickItem->isComponentComplete()
        qInfo( "p_waitWinQuickItem isVisible: %d",  p_waitWinQuickItem->isVisible() );
        p_timer->setInterval( 200 );
        p_timer->setSingleShot( true);
        p_timer->start();
        clicked = false;
        return true;
    }
    return false;
}

/*
*   Configuring for waiting logo rotating mechanism.
*/
void WaitWindowAnimation::imageRevolveInit()
{
    p_revolveTimer->setInterval( 100 );
    connect( p_revolveTimer, &QTimer::timeout, this, &WaitWindowAnimation::imageRevolve );
    p_revolveTimer->start();
    qDebug() << "p_revolveTimer started";
}

/*
*   This is waiting logo rotating slot function. Relevant signal is p_revolveTimer's
*   timeout.
*/
void WaitWindowAnimation::imageRevolve()
{
    // revolveIndex has range: [0, 4], rotating angle every time is 90 degree for avoiding to
    // make image change its size after transformed.
    ++revolveIndex;
    if( revolveIndex > 3 )
    {
        revolveIndex = 0;
    }
    // image rotate
    QMatrix rotatingMatrix;
    rotatingMatrix.rotate( ( 360.0 / 4 ) * revolveIndex );
    QPixmap pixmap(QString(":/Images/wait1.png"));
    QPixmap pix = pixmap.transformed( rotatingMatrix, Qt::SmoothTransformation );
    p_imgProvider->setPixmap( pix );
    qInfo() << rotatingMatrix << ", " << pix;

    // notify qml to update waiting image.
    qDebug( "rotate image update, revolveIndex is %d", revolveIndex );
    emit waitLogoRevolved();
}

/*
*   When p_waitWinComponent's status is Ready, we create p_waitWinQuickItem
*   and initialize the new qml window, make waiting logo rotating.
*/
void WaitWindowAnimation::finishCreateWaitWindow()
{
    qDebug() << p_waitWinComponent->status();

    if ( p_waitWinComponent->status() == QQmlComponent::Ready )
    {
        qDebug( "p_waitWinComponent status is Ready, clicked is %d", clicked );
        p_waitWinQuickItem = qobject_cast<QQuickItem*>( p_waitWinComponent->create() );
        if ( NULL == p_waitWinQuickItem )
        {
            qDebug( "Error creating object p_waitWinQuickItem");
        }
        else
        {
            p_waitWinQuickItem->setVisible( false );
            QQmlEngine::setObjectOwnership( p_waitWinQuickItem, QQmlEngine::CppOwnership );
            QQmlEngine::setObjectOwnership( p_waitWinComponent, QQmlEngine::CppOwnership );
            imageRevolveInit();
            if( clicked )
            {
                qDebug() << " user clicked \"to finish\" button.";
                if( !show() )
                {
                    qCritical() << "Didn't show waiting window.";
                }
            }
        }
    }
    else if ( p_waitWinComponent->status() == QQmlComponent::Error )
    {
        qDebug() << "Error loading p_waitWinComponent:" << p_waitWinComponent->errorString();
    }
}

/*
*   When got wait window QuickItem data, we would notify WindowGrabber to set frame rate and
*   start to combine images to generate gif file.
*/
void WaitWindowAnimation::combineImagesTrigger()
{
    if( p_waitWinQuickItem->isVisible() )
        emit startToCombineImages();
}

/*
*   ImagesCombiner would notify us to hide waiting window when gif file had been generated.
*   At same time, WindowGrabber would show "save as" window for user to save gif file.
*/
void WaitWindowAnimation::hide()
{
    p_waitWinQuickItem->setVisible( false );
    qInfo() << "p_waitWinQuickItem hide";
    emit disappeared();
}

/*
*   Get WaitWindowAnimation object's pointer. It is used in many scenes
*   such as qmlRegisterSingletonType callback funtion and connect function.
*/
WaitWindowAnimation *WaitWindowAnimation::getInstance(QQmlEngine *engine, QObject *parent)
{
     if( NULL == instance )
     {
         if( NULL == engine )
         {
             qCritical() << "engine is NULL.";
             return NULL;
         }
         instance = new WaitWindowAnimation( engine );
     }
     return instance;
}

/*
*   The function is call in QML file where transfers main window to cpp class WaitWindowAnimation.
*   Then we can show wait window on main window successfully.
*/
void WaitWindowAnimation::deliverMainWin(QVariant item)
{
    p_mainWindow = item.value<QQuickWindow *>();
#ifdef Q_OS_LINUX
    p_mainWindow->setIcon( QIcon("Images/logo.ico") );
#endif
    qDebug() << "got main window: " << p_mainWindow;
}

/*
*   Responsing function for user click "to finish" button.
*   We would show wait window after user clicked.
*/
void WaitWindowAnimation::toFinishClicked()
{
    if( NULL == p_waitWinQuickItem ||
            ( NULL != p_waitWinQuickItem && !p_waitWinQuickItem->isVisible() ) )
    {
        clicked = true;
    }

    if( !show() )
    {
        qWarning() << "Didn't show waiting window.";
    }
    else
    {
        clicked = false;
    }
}

/*
*   Destructor of WaitWindowAnimation.
*   We release all kinds of pointer resources.
*/
WaitWindowAnimation::~WaitWindowAnimation()
{
    if( NULL != p_waitWinComponent )
    {
        delete p_waitWinComponent;
        p_waitWinComponent = NULL;
    }

    if( NULL != p_waitWinQuickItem )
    {
        delete p_waitWinQuickItem;
        p_waitWinQuickItem = NULL;
    }

    if( NULL != p_timer )
    {
        delete p_timer;
        p_timer = NULL;
    }

    if( NULL != p_revolveTimer )
    {
        delete p_revolveTimer;
        p_revolveTimer = NULL;
    }

//  p_imgProvider would be free by QQMLEngine.
//    if( NULL != p_imgProvider )
//    {
//        delete p_imgProvider;
//        p_imgProvider = NULL;
//    }
}
