#ifndef NOTE_H
#define NOTE_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>

#include "markerbox.h"

class Note : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:
    void arrangeBoxes();

    // Selection boxes for the DragItem
    MarkerBox *markers[4];

public:

    Note(QGraphicsItem *parent = 0);
    Note(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);


};
#endif // NOTE_H
