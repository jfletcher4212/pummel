#ifndef SENARIOSTART_H
#define SENARIOSTART_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class SenarioStart : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

public:

    SenarioStart(QGraphicsItem *parent = 0);
    SenarioStart(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos);

};

#endif // SENARIOSTART_H
