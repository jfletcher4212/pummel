#ifndef ACTOR_H
#define ACTOR_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class Actor : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();
    int m_labelheight, m_labelwidth;

private:

    void arrangeBoxes();

public:

    Actor(QPointF = QPointF(0,0), QGraphicsItem *parent = 0);
    Actor(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos, QString contents);


};

#endif // ACTOR_H
