/**********************************************************
*
* @brief    Declaration of CPP class WaitImageProvider which
*           offers image source for QML Image.
*
* @author   theArcticOcean
***********************************************************/

#ifndef WAITIMAGEPROVIDER_H
#define WAITIMAGEPROVIDER_H

#include <QQuickImageProvider>

class WaitImageProvider : public QQuickImageProvider
{
public:
    WaitImageProvider();
    virtual ~WaitImageProvider();
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    void setPixmap( const QPixmap & _pixmap );

private:
    QPixmap pixmap;
};

#endif // WAITIMAGEPROVIDER_H
