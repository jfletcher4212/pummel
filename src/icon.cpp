/* icon.cpp -contains the functions to store default properties in the shape structs
               and contains the creation function for each shape
               Made by Theora Rice
  */
#include "icon.h"
#include <QtGui>


icon::icon()
{

}

int icon::getXPos()
{
    return baseIcon.posx;
}

int icon::getYPos()
{
    return baseIcon.posy;
}

void icon::setPos(int newXPos, int newYPos)
{
    baseIcon.posx = newXPos;
    baseIcon.posy = newYPos;
}

int icon::getXSize()
{
    return baseIcon.xsize;
}

int icon::getYSize()
{
    return baseIcon.ysize;
}

void icon::setSize(int newXSize, int newYSize)
{
    baseIcon.xsize = newXSize;
    baseIcon.ysize = newYSize;

}

QString icon::reportShapetype()
{
    return baseIcon.shapetype;
}

void icon::setShapetype(QString shapename)
{
    baseIcon.shapetype = shapename;
}

int icon::getID()
{
    return baseIcon.iD;
}
