#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"
class ellipse : public icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

public:

    ellipse(QGraphicsItem *parent = 0);
    ellipse(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);


};

#endif // ELLIPSE_H
