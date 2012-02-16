/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef icon_H
#define icon_H

#include <QWidget>
#include <QGraphicsItem>

int next_ID = 1;

class icon : public QGraphicsItem
{
protected:

    //Struct to contain basic properties all shapes share
    struct baseIcon
    {
        int iD;
        int posx;
        int posy;
        int xsize;
        int ysize;
        QString shapetype;
    };

public:

    icon();
    int getXPos();
    int getYPos();
    void setPos(int newXPos, int newYPos);
    int getXSize();
    int getYSize();
    void setSize(int newXSize, int newYSize);
    QString reportShapetype();
    void setShapetype(QString shapename);
    int getID();
};

#endif // shapes_H
