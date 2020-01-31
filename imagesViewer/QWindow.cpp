#include "QWindow.h"
#include "logprinter.h"

#include <stdio.h>
#include <QPalette>
#include <algorithm>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QCoreApplication>

using namespace std;

QWindow::QWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWindow),
    gLayout( new QGridLayout )
{
    ui->setupUi( this );
    QPalette pal( ui->centralWidget->palette() );
    pal.setColor( QPalette::Background, Qt::white );
    ui->centralWidget->setAutoFillBackground( true );
    ui->centralWidget->setPalette( pal );
    QString filePath = QCoreApplication::applicationDirPath();
    qDebug() << "applicationDirPath: " << filePath;
    filePath = filePath + "/images/add.png";
    ui->addLabel->setPixmap( QPixmap( filePath ) );
    startWinRect = QRect( geometry() );
    startAllLabelRect = QRect( ui->addLabel->geometry() );

    QDesktopWidget *desktop = QApplication::desktop();
    qDebug() << "screenGeometry: " << desktop->screenGeometry();
    qDebug() << "availableGeometry: " << desktop->availableGeometry();

    availableWidth = desktop->availableGeometry().width();
    availableHeight = desktop->availableGeometry().height();

    connect( ui->actionClose_All, &QAction::triggered, this, &QWindow::actionCloseAll_triggered );
    connect( ui->actionOpen_Files, &QAction::triggered, this, &QWindow::actionOpenFiles_triggered );

    // ui->centralWidget has not layout defaultly.
    ui->centralWidget->setLayout( gLayout );
    ui->addLabel->setMaximumSize( 170, 100 );
    gLayout->addWidget( ui->addLabel, 0, 0, 1, 1 );
    ui->addLabel->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
}

QWindow::~QWindow()
{
    delete ui;
    CPP_FREE( gLayout )
}

void QWindow::actionCloseAll_triggered()
{
    if( !acceptDrops() )
    {
        clearImages();
        ui->addLabel->setGeometry( startAllLabelRect );
        setAcceptDrops( true );
        DataManager::getInstance()->m_validImageCount = 0;
        ui->addLabel->setHidden( false );
        gLayout->addWidget( ui->addLabel, 0, 0, 1, 1 );

        // After remove QLabel's pixmap, we need to resize it.
        adjustSize();

        // setGeometry( startWinRect ) is not reliant, because Geometry.x() and Geometry.y() return 0
        // althrough window is at center on windows platform.
        setGeometry( int(availableWidth/2 - startWinRect.width()/2),
                     int(availableHeight/2 - startWinRect.height()/2) + 10,
                     startWinRect.width(),
                     startWinRect.height() );
        qDebug() << size();
    }
}

void QWindow::actionOpenFiles_triggered()
{
    QString suffixes = "";
    suffixes = suffixes + QString("*.png") + " " +
                QString("*.PNG") + " " +
                QString("*.jpg") + " " +
                QString("*.JPG") + " " +
                QString("*.bmp") + " " +
                QString("*.BMP") + " " +
                QString("*.jpeg") + " " +
                QString("*.JPEG");

    QStringList fileNames = QFileDialog::getOpenFileNames( this,
         tr("Open Image"), "/home", tr("Image Files (") + suffixes + tr(")") );
    if( m_photoFrames.size() > 0 || fileNames.size() <= 0 )
    {
        qDebug() << "m_photoFrames.size(): " << m_photoFrames.size() << ", fileNames.size(): " << fileNames.size();
        return ;
    }
    DataManager::getInstance()->m_validImageCount = fileNames.size();
    qDebug() << "fileNames.size(): " << fileNames.size();
    for( int i = 0; i < fileNames.size(); ++i )
    {
        DataManager::getInstance()->m_filePaths.push_back( QUrl( QString("file://") + fileNames.at(i) ) );
    }

    updateDisplay();
}

void QWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent: " << event->mimeData()->formats();
    if( m_photoFrames.size() > 0 )
    {
        qDebug() << "m_photoFrames.size() > 0";
        return ;
    }
    DataManager::getInstance()->m_validImageCount = 0;
    int count =  0;
    for( auto url: event->mimeData()->urls() )
    {
        if( isValidImage( url.toLocalFile() ) )
        {
            ++count;
            DataManager::getInstance()->m_filePaths.push_back( url );
        }
    }

    DataManager::getInstance()->m_validImageCount = count;
    if( DataManager::getInstance()->m_validImageCount >  MAX_NUMBER_OF_IMAGES )
    {
        QMessageBox msg;
        msg.setIcon( QMessageBox::Warning );
#ifdef Q_OS_WIN
        msg.setWindowIcon( QIcon("udesign pics/ulab_icon.ico") );
#endif
        msg.addButton( "Ok", QMessageBox::AcceptRole );
        msg.setWindowTitle( "Attention" );
        msg.setText( QString("The number of images showed can't be greater than ") + QString::number( MAX_NUMBER_OF_IMAGES ) );
        msg.exec();
        return ;
    }

    if( DataManager::getInstance()->m_validImageCount > 0 )
    {
        event->acceptProposedAction();
    }
}

void QWindow::dropEvent(QDropEvent *event)
{
    qDebug() << "dropEvent: ";

    if( acceptDrops() )
    {
        updateDisplay();
    }
}

void QWindow::updateDisplay()
{
    // Make the whole window has max size that center widget can own.
    int width = min(availableWidth, availableHeight)
            - ui->menuBar->geometry().height()
            - ui->mainToolBar->geometry().height()
            - ui->statusBar->geometry().height();
    int height = width;

    setGeometry( int(availableWidth/2 - width/2),
                 int(availableHeight/2 - height/2) + 10,
                 width,
                 height );

    setAcceptDrops( false );
    ui->addLabel->setHidden( true );
    gLayout->removeWidget( ui->addLabel );

    createCase( DataManager::getInstance()->m_validImageCount - 1 );
}

bool QWindow::isValidImage(const QString filePath)
{
    if( filePath.endsWith( QString(".png") ) ||
        filePath.endsWith( QString(".PNG") ) ||
        filePath.endsWith( QString(".jpg") ) ||
        filePath.endsWith( QString(".JPG") ) ||
        filePath.endsWith( QString(".bmp") ) ||
        filePath.endsWith( QString(".BMP") ) ||
        filePath.endsWith( QString(".jpeg") ) ||
        filePath.endsWith( QString(".JPEG") ) )
    {
        return true;
    }
    return false;
}

void QWindow::createCase(const unsigned short index)
{
    if( index > MAX_NUMBER_OF_IMAGES - 1 )
    {
        qWarning() << "index is bigger than " << MAX_NUMBER_OF_IMAGES - 1;
        return ;
    }
    vector<int> layoutArray = DataManager::getInstance()->Getm_layouts()[index];
    for( int i = 0; i <= index; ++i )
    {
        m_photoFrames.push_back( QSharedPointer<PhotoFrame>( new PhotoFrame() ) );
    }
    
    int imageIndex = 0;
    int columnCount = 0;
    for( int i = 0; i < layoutArray.size(); ++i )
    {
        columnCount = max( columnCount, layoutArray[i] );
    }

    for( int row = 0; row < layoutArray.size(); ++row )
    {
        int cols = layoutArray[row];
        int delta = columnCount - cols;
        printer( "row is %d, cols is %d, columnCount is %d", row, cols, columnCount );
        int *colArray = getColArray( cols, delta );
        int colIndex = 0;
        for( int col = 0; col < layoutArray[row]; ++col )
        {
            m_photoFrames[imageIndex]->ReadPhoto(imageIndex, 200, 200);
            gLayout->addWidget( m_photoFrames[imageIndex]->Getm_frame(), row, colIndex, 1, colArray[col] ); // Qt::AlignCenter Qt::AlignJustify Qt::AlignBaseline
            colIndex = colIndex + colArray[col];
            ++imageIndex;
        }
        delete colArray;
        colArray = nullptr;
    }
}

void QWindow::clearImages()
{
    int count = gLayout->count();
    for( int i = 0; i < count; ++i )
    {
        gLayout->removeWidget( m_photoFrames[i]->Getm_frame() );
        ui->centralWidget->adjustSize();
        m_photoFrames[i]->RemovePhotoFromUI();
    }
    DataManager::getInstance()->m_filePaths.clear();
    m_photoFrames.clear();
}

/*
*   getColArray is used to calculate the number of column for every image cell on one row.
*/
int *QWindow::getColArray( const int columnNumber, const int delta )
{
    printer( "columnNumber is %d, delta is %d", columnNumber, delta );
    int *array = new int[ columnNumber ];
    for( int i = 0; i < columnNumber; ++i )
    {
        array[i]  = 1;
    }
    int del1 = delta / 2;
    int del2 = delta - del1;
    while( del1 > 0 )
    {
        array[del1]++;
        del1--;
    }
    int index = del1 + 1;
    if( del1 == 0 && del2 > 0 )
    {
        index = 0;
    }
    while( del2 > 0 && index < columnNumber )
    {
        array[index] ++;
        del2--;
    }
    for( int i = 0; i < columnNumber; ++i )
    {
        printf( "%d ", array[i] );
    }
    puts( "" );
    return array;
}
