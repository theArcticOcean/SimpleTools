/**********************************************************
*
* @brief    The details for class PointManager which records
*           position and size of Gif window that red line
*           area.
*
* @author   theArcticOcean
***********************************************************/

#include "pointmanager.h"
#include <math.h>

/*
*   Constructor of class PointManager
*/
PointManager::PointManager
    (
    QObject *parent
    )
    : QObject(parent)
    , leftTop( 0, 0 )
    , rightBottom( 0, 0 )
{

}

/*
*   Record the position of left-top point of red line area.
*/
void PointManager::setLeftTopPoint(double x, double y)
{
    leftTop.setX( x );
    leftTop.setY( y );
    emit leftTopXChanged();
    emit leftTopYChanged();
}

/*
*   Record the position of right-bottom point of red line area.
*/
void PointManager::setRightBottomPoint(double x, double y)
{
    rightBottom.setX( x );
    rightBottom.setY( y );
    emit widthChanged();
    emit heightChanged();
}

/*
*   Get the width of record live area.
*/
double PointManager::getWidth()
{
    return fabs( rightBottom.x() - leftTop.x() );
}

/*
*   Get the height of record live area.
*/
double PointManager::getHeight()
{
    return fabs( rightBottom.y() - leftTop.y() );
}

/*
*   Get left-top point's x value
*/
double PointManager::getLeftTopX()
{
    return leftTop.x();
}

/*
*   Get left-top point's y value.
*/
double PointManager::getLeftTopY()
{
    return leftTop.y();
}
