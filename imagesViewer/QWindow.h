#ifndef QWindow_H
#define QWindow_H

#include "ui_QWindow.h"
#include "datamanager.h"

#include <QMainWindow>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>

#include "photoframe.h"

namespace Ui {
class QWindow;
}

class QWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWindow(QWidget *parent = 0);
    ~QWindow();

public slots:
    void actionCloseAll_triggered();
    void actionOpenFiles_triggered();

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    void updateDisplay();
    bool isValidImage( const QString filePath );
    void createCase( const unsigned short index );
    void clearImages();
    int *getColArray(const int columnNumber, const int delta);

private:
    Ui::QWindow *ui;
    QGridLayout *gLayout;
    QRect startWinRect;
    QRect startAllLabelRect;
    double availableWidth;
    double availableHeight;

    QVector< QSharedPointer<PhotoFrame> > m_photoFrames;
};

#endif // QWindow_H
