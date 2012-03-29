#ifndef ACTOR_H
#define ACTOR_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"

class actor : public Icon
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

    actor(QGraphicsItem *parent = 0);
    actor(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);


};

#endif // ACTOR_H
