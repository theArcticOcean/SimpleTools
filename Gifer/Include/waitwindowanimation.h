/**********************************************************
*
* @brief    Class WaitWindowAnimation is used to show waiting
*           window when software is generating gif file.
*
* @author   theArcticOcean
***********************************************************/

#ifndef WAITWINDOWANIMATION_H
#define WAITWINDOWANIMATION_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QThread>
#include <QTimer>

#include "waitimageprovider.h"

class WaitWindowAnimation : public QObject
{
    Q_OBJECT
public:
    static WaitWindowAnimation* getInstance( QQmlEngine *engine = nullptr, QObject *parent = nullptr );

    Q_INVOKABLE void deliverMainWin( QVariant item );
    Q_INVOKABLE void toFinishClicked();

    WaitImageProvider *p_imgProvider;

signals:
    void disappeared();
    void startToCombineImages();
    void stopGrab();
    void waitLogoRevolved();

public slots:
    void finishCreateWaitWindow();
    void combineImagesTrigger();
    void hide();
    void imageRevolve();

private:
    explicit WaitWindowAnimation(QQmlEngine *engine, QObject *parent = nullptr);
    ~WaitWindowAnimation();
    bool show();
    void imageRevolveInit();

    QQmlEngine *p_qmlEngine;
    QQmlComponent *p_waitWinComponent;
    QQuickWindow *p_mainWindow;
    QImage *p_image;
    QQuickItem *p_waitWinQuickItem;
    QTimer *p_timer;
    QTimer *p_revolveTimer;

    static WaitWindowAnimation* instance;

    unsigned char revolveIndex;
    bool clicked;     // Record whether user clicked "to finish" button.
};

#endif // WAITWINDOWANIMATION_H
