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
    void setShape(ShapeType newShape){shape = newShape;}
    void setSize(int newWidth, int newHeight){width = newWidth; height = newHeight;}
    void setState(int x){state = x;}
    void setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d);

    // Accessors
    QList<DragItem*> getConnections();
    int getWidth(){return width;}
    int getHeight(){return height;}
    int getId(){return id;}
    int getState(){return state;}
    MarkerBox* getMarkerBox(int i){return markers[i];}


protected:
    QRectF boundingRect() const{return QRectF(0,0,width, height);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    // DragItem id counter
    static int next_id;

    // used for zValue stacking and item selection
    int state;

    // DragItem parameters
    int width;
    int height;
    ShapeType shape;

    // ID number for individual objects
    int id;

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

};

#endif // DRAGITEM_H
