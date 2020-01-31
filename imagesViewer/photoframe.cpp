#include "photoframe.h"
#include "datamanager.h"
#include <QWidget>
#include <QDebug>

PhotoFrame::PhotoFrame()
    : m_frame( new QGroupBox )
{
    m_frame->setLayout( &m_vLayout );
    m_frame->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_vLayout.setContentsMargins( 2, 2, 2, 2 );
    m_image.setScaledContents( true );
    m_vLayout.addWidget( &m_image );
}

PhotoFrame::~PhotoFrame()
{
    if( nullptr != m_frame )
    {
        // delete m_frame; //we need not to delete m_frame, because QLayout::removeWidget has done it.
        m_frame = nullptr;
    }
}

void PhotoFrame::SetTitle(const QString title)
{
    m_frame->setTitle( title );
    m_frame->setAlignment( Qt::AlignHCenter );
}

void PhotoFrame::RemovePhotoFromUI()
{
    m_image.clear();
    m_image.adjustSize();
    m_frame->adjustSize();
    m_frame->setHidden( true );
}

void PhotoFrame::ReadPhoto(const int urlIndex, const int w, const int h)
{
    QString filePath = DataManager::getInstance()->m_filePaths[ urlIndex ].toLocalFile();
    QString name = filePath;
    qDebug() << DataManager::getInstance()->m_filePaths.size() << " | " << urlIndex << ", " << name;
#ifdef Q_OS_MAC
    name = name.split("/").last();
#elif defined  Q_OS_WIN
    name = name.split("/").last();  // same as mac
#endif
    SetTitle( name );
    //QPixmap pixmap( filePath );
    //int _w = max( pixmap.width(), w );
    //int _h = max( pixmap.height(), h );
    //m_image.setPixmap( QPixmap( filePath ).scaled( QSize(_w, _h), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );
    //m_image.setPixmap( QPixmap( filePath ).scaled( QSize(w, h), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );
    m_image.setPixmap( QPixmap( filePath ).scaled( QSize(w, h) ) );
    m_frame->setHidden( false );
}
