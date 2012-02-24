/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef icon_H
#define icon_H

#include <QWidget>
#include <QGraphicsItem>

//int next_ID = 1;

class icon : public QGraphicsItem
{
protected:

    int m_iD;
    int m_xpos;
    int m_ypos;
    int m_xsize;
    int m_ysize;
    QString m_shapetype;

    static int m_next_id;

public:

    icon(QGraphicsItem *parent = 0);
    int getXPos();
    int getYPos();
    void setPos(int newXPos, int newYPos);   // simple accessor and mutator methods for the position
    int getXSize();
    int getYSize();
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    QString reportShapetype();
    void setShapetype(QString shapename);     // simple accessor and mutator methods for the shapetype
    int getID();                              // simple accessor for getting the ID
};

#endif // shapes_H
