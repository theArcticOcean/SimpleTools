/**********************************************************
*
* @brief    Class WindowGrabber is responsible to grab Gif
*           window.
*
* @author   theArcticOcean
***********************************************************/

#ifndef WINDOWGRABBER_H
#define WINDOWGRABBER_H

#include <QWidget>
#include <QTimer>
#include <QScreen>
#include <QVariant>
#include "imagescombiner.h"

class WindowGrabber : public QWidget
{
    Q_OBJECT
public:
    static WindowGrabber *getInstance();
    ~WindowGrabber();

    Q_INVOKABLE void startGrab( const double &x, const double &y, const double &w, const double &h );
    Q_INVOKABLE void setFramePerSec( const int rate );
    Q_INVOKABLE void combineImages();

signals:

public slots:
    void grabWindow();
    void saveGif();
    void onStopGrab();

private:
    WindowGrabber();
    void clearImagesFolder();

    QTimer grabTimer;
    QString imageFolderPath;

    int rectX;
    int rectY;
    int rectWidth;
    int rectHeight;

    int imageCount;
    int framePerSec;

    static WindowGrabber *instance;
    ImagesCombiner *p_imageCombiner;
};

#endif // WINDOWGRABBER_H
