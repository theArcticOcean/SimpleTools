#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QDialog>

#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <QVTKOpenGLWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QDialog
{
    Q_OBJECT

public:
    static DisplayWindow* getInstance();
    ~DisplayWindow();
    void fetchFilePath( const QString path );
    void refresh();

private slots:
    void on_pushButton_clicked();

private:
    explicit DisplayWindow(QWidget *parent = 0);

    vtkSmartPointer<vtkSTLReader> reader;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

    static DisplayWindow *instancePtr;
    Ui::DisplayWindow *ui;
    QString filePath;
};

#endif
