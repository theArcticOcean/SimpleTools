/**********************************************************
*
* @brief    This source file provides a way to print log into
*           local file in QT development environment.
*
* @author   theArcticOcean
***********************************************************/

#ifndef LOGPRINTER_HPP
#define LOGPRINTER_HPP

#include <unistd.h>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QCoreApplication>

// QtGlobal has many basic function such as qCritical()
#include <QtGlobal>

#define BUFFER_SIZE 1024*10

#define DEBUG_SLIENCE 1

#define printer(fmt,args...) ImagesViewer::print( __FILE__, __LINE__, __FUNCTION__, fmt, ##args )

namespace ImagesViewer {

    static QString logFilePath;
    void LogInit();

    void LogBase(
            QtMsgType type,
            const QMessageLogContext &context = QMessageLogContext( __FILE__, __LINE__, __FUNCTION__, NULL ),
            const QString &msg = QString("")
            );

    void print(const char *file, const int line, const char *func,const char *fmt, ...);
}

#endif // LOGPRINTER_HPP
