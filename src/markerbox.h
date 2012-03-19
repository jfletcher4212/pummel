#ifndef MARKERBOX_H
#define MARKERBOX_H

#include <QtGui>
#include <QGraphicsItem>

class MarkerBox : public QGraphicsItem
{
public:
    MarkerBox(QGraphicsItem *parent = 0);
    QRectF boundingRect() const{return QRectF(0,0,width,height);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // Mutators
    void setId(int x){id = x;};

private:
    int itemIndex; //index in scene_items of DragScene that this markerbox references
    int id; // 0 = upper left, 1 = upper right, 2 = lower left, 3 = lower right.  The number indicates the boxes position around the object
    int startX; // original X coordinate (in scene coordinates) of the markerbox (used in mousePressEvent)
    int startY; // original Y coordinate (in scene coordinates) of the markerbox (used in mousePressEvent)

    int width; // set to 5, adjust in constructor if needed
    int height; // set to 5, adjust in constructor if needed
};

#endif // MARKERBOX_H
