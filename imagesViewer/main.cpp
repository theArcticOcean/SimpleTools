#include "QWindow.h"
#include "logprinter.h"

#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setbuf(stdout, NULL);
    ImagesViewer::LogInit();
    qInstallMessageHandler( ImagesViewer::LogBase );

    QWindow w;
#ifdef Q_OS_LINUX
    w.setWindowIcon( QIcon( "images/logo.ico" ) );
#endif
    w.show();
    return a.exec();
}
