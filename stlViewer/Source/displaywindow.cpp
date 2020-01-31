#include "ui_displaywindow.h"
#include "displaywindow.h"
#include "openfiledialog.h"

#include <QDebug>

DisplayWindow* DisplayWindow::instancePtr = nullptr;

DisplayWindow::DisplayWindow(QWidget *parent)
    : QDialog( parent )
    , ui( new Ui::DisplayWindow )
{
    ui->setupUi(this);

    reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName( "filename.stl" );
    reader->Update();

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection( reader->GetOutputPort() );

    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper( mapper );

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground( 0, 0, 0 ); // Background color green

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->qvtkWidget->SetRenderWindow( renderWindow );
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
}

/*
*   We just need to update reader, pipeline mechanism would works.
*/
void DisplayWindow::refresh()
{
    reader->SetFileName( filePath.toStdString().c_str() );
    reader->Update();
    renderer->ResetCamera();
}

DisplayWindow *DisplayWindow::getInstance()
{
    if( nullptr == instancePtr )
    {
        instancePtr = new DisplayWindow();
    }
    return instancePtr;
}

DisplayWindow::~DisplayWindow()
{

}

void DisplayWindow::fetchFilePath(const QString path)
{
    filePath = path;
}

void DisplayWindow::on_pushButton_clicked()
{
    this->hide();
    OpenFileDialog::getInstance()->show();
}
