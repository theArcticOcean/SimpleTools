#include <QApplication>
#include <QIcon>

#include "openfiledialog.h"
#include "displaywindow.h"
#include "logprinter.h"

int main(int argc, char *argv[])
{
    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);
    OpenFileDialog::getInstance()->show();
    LogInit();
    printer( "Program start!" );

    QString iconPath = QCoreApplication::applicationDirPath();
#ifdef Q_OS_MAC
    iconPath = iconPath + "/Images/logo.icns";
#elif defined Q_OS_WIN
    iconPath = iconPath + "/Images/logo.ico";
#endif
    a.setWindowIcon( QIcon( iconPath ) );

    return a.exec();
}
