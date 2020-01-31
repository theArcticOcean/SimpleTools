#ifndef LOGPRINTER_HPP
#define LOGPRINTER_HPP

#include <QDebug>
#include <unistd.h>
#include <QString>
#include <QCoreApplication>
#include <QtGlobal>

static QString logFilePath;

#define printer(fmt,args...) \
    print( __FILE__, __LINE__, fmt, ##args )

void LogInit();

void print(const char *file, const int line, const char *fmt, ...);

#endif
