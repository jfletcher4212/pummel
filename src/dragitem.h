/*
 * Reimplementation of QGraphicsItem
 * Holds object data
 *
 */

#ifndef DRAGITEM_H
#define DRAGITEM_H

#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"

// Shape types
enum ShapeType {Square, Pill, Ellipse, Rectangle, Circle};

class DragItem : public QGraphicsItem
{
public:
    DragItem(QGraphicsItem *parent = 0);

    // Mutators
    void setShape(ShapeType shape);
    void setSize(int newWidth, int newHeight);

    // Accessors
    int getWidth();
    int getHeight();
    int getId();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    // DragItem id counter
    static int next_id;

    // DragItem parameters
    int width;
    int height;
    ShapeType shape;
    int id;

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

};

#endif // DRAGITEM_H
