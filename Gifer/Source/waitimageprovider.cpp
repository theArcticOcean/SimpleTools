/**********************************************************
*
* @brief    The file provide details for class WaitImageProvider
*           which offers image source for QML Image.
*
* @author   theArcticOcean
***********************************************************/

#include "waitimageprovider.h"
#include <QDebug>

/*
*   Constructor of class WaitImageProvider
*/
WaitImageProvider::WaitImageProvider()
    : QQuickImageProvider( QQmlImageProviderBase::Pixmap )
{

}

/*
*   Destructor of WaitImageProvider
*/
WaitImageProvider::~WaitImageProvider()
{

}

/*
*   WaitImageProvider provide image source for QML Image.
*/
QPixmap WaitImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    qInfo() << "requestPixmap...";
    return pixmap;
}

/*
*   The function is provided to the outside.
*/
void WaitImageProvider::setPixmap(const QPixmap &_pixmap)
{
    pixmap = _pixmap;
}
