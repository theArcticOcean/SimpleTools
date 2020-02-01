/**********************************************************
*
* @brief    The main entry for Gifer software.
*
* @author   theArcticOcean
***********************************************************/

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>

#include "pointmanager.h"
#include "windowgrabber.h"
#include "logprinter.hpp"
#include "waitwindowanimation.h"

static QObject *singletonType_PointManager_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new PointManager();
}

static QObject *singletonType_WindowGrabber_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return WindowGrabber::getInstance();
}

static QObject *singletonType_WaitWindowAnimation_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)

    return WaitWindowAnimation::getInstance( engine );
}

int main(int argc, char *argv[])
{
/*
 * If we want to hide cmd for MSVC, use the following statement.
 *
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"WinMainCRTStartup\"")
*/

    QApplication app(argc, argv);

    GiferSpace::LogInit();
    qInstallMessageHandler( GiferSpace::LogBase );
    qDebug() << "LogInit finished.";

    qmlRegisterSingletonType<PointManager>( "Share.core", 1, 0, "PointManager", singletonType_PointManager_provider );
    qmlRegisterSingletonType<WindowGrabber>( "Share.core", 1, 0, "WindowGrabber", singletonType_WindowGrabber_provider );
    qmlRegisterSingletonType<WaitWindowAnimation>( "Share.core", 1, 0, "WaitWindowAnimation", singletonType_WaitWindowAnimation_provider );

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    engine.addImageProvider( QString("waitImageProvider"), WaitWindowAnimation::getInstance()->p_imgProvider );
#ifdef Q_OS_LINUX
    app.setWindowIcon( QIcon("Images/logo.ico") );
#endif
    return app.exec();
}
