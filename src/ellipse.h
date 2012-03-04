#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"
class ellipse : public icon
{


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
   // void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    // DragItem id counter         // also done in parent class
    //static int next_id;

    // DragItem parameters
    //int width;
    //int height;
    //ShapeType shape;
    //int id;

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

public:

    ellipse(QGraphicsItem *parent = 0);
    ellipse(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);

    // Accessors            // done in parent class
    //int getWidth();
    //int getHeight();
    //int getId();

};

#endif // ELLIPSE_H
