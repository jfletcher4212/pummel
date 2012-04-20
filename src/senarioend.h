#ifndef SENARIOEND_H
#define SENARIOEND_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class SenarioEnd : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

public:

    SenarioEnd(QGraphicsItem *parent = 0);
    SenarioEnd(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);

};

#endif // SENARIOEND_H
