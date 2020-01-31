#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>

#include "logprinter.h"

using namespace std;

#include "openfiledialog.h"
#include "ui_openfiledialog.h"
#include "displaywindow.h"

OpenFileDialog* OpenFileDialog::instancePtr = nullptr;

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    ui->setupUi(this);
    setFixedHeight( 455 );
    setFixedWidth( 647 );
    QString pixmapPath = QCoreApplication::applicationDirPath();
    pixmapPath = pixmapPath + "/Resource/Earth.png";
    ui->pictureLabel->setPixmap( QPixmap(pixmapPath) );
    ui->pictureLabel->setScaledContents( true );

    recordFilePath = QCoreApplication::applicationDirPath();
    recordFilePath = recordFilePath + "/Resource/.record";

    // if the .record file doesn't exist, we create it.
    if( access( recordFilePath.toStdString().c_str(), F_OK ) )
    {
        assert( nullptr != fopen( recordFilePath.toStdString().c_str(), "w" ) );
    }

    readPath();
}

int OpenFileDialog::writePath()
{
    if(  0 == access( recordFilePath.toStdString().c_str(), F_OK ) )
    {
        if( truncate( recordFilePath.toStdString().c_str(), 0 ) )
        {
            perror( "truncate " );
        }
    }
    FILE *filePtr = fopen( recordFilePath.toStdString().c_str(), "w" );
    assert( filePtr != nullptr );  // if it doesn't satisfy condition, assert works.
    int bytes = fprintf( filePtr, ui->lineEdit->text().toStdString().c_str() );
    printer( "fprintf %d bytes.", bytes );
    return bytes;
}

void OpenFileDialog::readPath()
{
    FILE *filePtr = fopen( recordFilePath.toStdString().c_str(), "r" );
    assert( filePtr != nullptr );  // if it doesn't satisfy condition, assert works.
    char buffer[1024];
    fscanf( filePtr, "%s", buffer );
    ui->lineEdit->setText( buffer );
}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}

OpenFileDialog *OpenFileDialog::getInstance()
{
    if( nullptr == instancePtr )
    {
        instancePtr = new OpenFileDialog;
    }
    return instancePtr;
}

void OpenFileDialog::on_displayButton_clicked()
{
    if( access( ui->lineEdit->text().toStdString().c_str(), F_OK ) )
    {
        QMessageBox message;
        message.setWindowIcon( QIcon(":/logo.png") );
        message.setWindowTitle( "Notice" );
        message.setText( tr("The file is not there any more.") );
        message.setDefaultButton( QMessageBox::Ok );
        message.exec();
        return ;
    }

    DisplayWindow::getInstance()->fetchFilePath( ui->lineEdit->text() );
    DisplayWindow::getInstance()->refresh();
    DisplayWindow::getInstance()->show();

    this->hide();
    writePath();
}

void OpenFileDialog::on_browseButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle( tr("Choose A STL File") );
    if( ui->lineEdit->text().length() > 1 )
    {
        // go to last directory.
        dialog.setDirectory(  QDir( ui->lineEdit->text() ) );
    }
    else
    {
        dialog.setDirectory(  QDir(".") );
    }
    dialog.setNameFilter( "*.stl" );
    dialog.setFileMode( QFileDialog::ExistingFiles );
    dialog.setViewMode( QFileDialog::Detail );
    QStringList fileList;
    if( QDialog::Accepted == dialog.exec() )
    {
        fileList = dialog.selectedFiles();
    }
    else // QDialog::Rejected
    {
        return ;
    }

    if( fileList.count() > 1 )
    {
        QMessageBox message;
        message.setWindowIcon( QIcon(":/logo.png") );
        message.setWindowTitle( "Notice" );
        message.setText( tr("Please choose only one stl file.") );
        message.setDefaultButton( QMessageBox::Ok );
        message.exec();
        ui->lineEdit->setText( tr("") );
    }
    else
    {
        ui->lineEdit->setText( fileList[0] );
    }
}
