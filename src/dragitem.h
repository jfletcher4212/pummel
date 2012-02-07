/*
 * Reimplementation of QGraphicsItem
 * Holds object data
 *
 */

#ifndef DRAGITEM_H
#define DRAGITEM_H

#include <QtGui>
#include <QGraphicsItem>

enum ShapeType {Square, Pill, Ellipse, Rectangle, Circle};


class DragItem : public QGraphicsItem
{
public:
    /*
      This is the DragItem constructor, it defaults to a 'base' rectangle of 25x25.  Will probably adapt
      a constructor to take a shape object as a parameter.  The object passed in would need to have its 'base'
      rectangle and some way of determining what kind of shape it is (I was thinking enum, prototype is above).
      */
    DragItem(QGraphicsItem *parent = 0);
    //DragItem(QGraphicsItem *parent = 0, QRectF newRect = QRectF(0,0,25,25), ShapeType newShape = Rectangle);
    void setBase(QRectF newBase);
    void setShape(ShapeType shape);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void paintSquare(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF base;
    ShapeType shape;
    /*
      Since all QT images are drawn from rectangles are figured we could use a base rectangle for just about all
      drawing and it would hopefully make them easily scalable.
      */
};

#endif // DRAGITEM_H
