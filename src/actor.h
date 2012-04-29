#ifndef ACTOR_H
#define ACTOR_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"

class Actor : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:
    void arrangeBoxes();

public:

    Actor(QGraphicsItem *parent = 0);
    Actor(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString contents);


};

#endif // ACTOR_H
