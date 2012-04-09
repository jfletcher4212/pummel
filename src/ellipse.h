#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class Ellipse : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:

    void arrangeBoxes();

public:

    Ellipse(QGraphicsItem *parent = 0);
    Ellipse(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);

};

#endif // ELLIPSE_H
