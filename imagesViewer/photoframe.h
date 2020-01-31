#ifndef PHOTOFRAME_H
#define PHOTOFRAME_H

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QSharedPointer>

#include "macrodefined.hpp"

class PhotoFrame
{
public:
    PhotoFrame();
    virtual ~PhotoFrame();
    void SetTitle( const QString title );
    void RemovePhotoFromUI();
    void ReadPhoto( const int urlIndex, const int w, const int h );
    CPP_GET_MACRO( m_frame, QGroupBox* )

private:
    QGroupBox *m_frame;
    QVBoxLayout m_vLayout;
    QLabel m_image;
};

#endif // PHOTOFRAME_H
