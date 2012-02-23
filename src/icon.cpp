/* icon.cpp -contains the functions to store default properties in the shape structs
               and contains the creation function for each shape
               Made by Theora Rice
  */
#include "icon.h"
#include <QtGui>


int icon::m_next_id = 1;

icon::icon(QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

int icon::getXPos()
{
    return m_xpos;
}

int icon::getYPos()
{
    return m_ypos;
}

void icon::setPos(int newXPos, int newYPos)
{
    m_xpos = newXPos;
    m_ypos = newYPos;
}

int icon::getXSize()
{
    return m_xsize;
}

int icon::getYSize()
{
    return m_ysize;
}

void icon::setSize(int newXSize, int newYSize)
{
    m_xsize = newXSize;
    m_ysize = newYSize;

}

QString icon::reportShapetype()
{
    return m_shapetype;
}

void icon::setShapetype(QString shapename)
{
    m_shapetype = shapename;
}

int icon::getID()
{
    return m_iD;
}
