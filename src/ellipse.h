#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"
class ellipse : icon
{
public:
    ellipse(QGraphicsItem *parent = 0);

    // Accessors
    //int getWidth();
    //int getHeight();
    //int getId();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    // DragItem id counter
    //static int next_id;

    // DragItem parameters
    //int width;
    //int height;
    //ShapeType shape;
    //int id;

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

};

#endif // ELLIPSE_H
