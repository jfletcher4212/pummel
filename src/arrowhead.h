#ifndef ARROWHEAD_H
#define ARROWHEAD_H

#include "basiclineobject.h"

enum AHType{Solid_AH};

class arrowhead : public BasicLineObject
{
public:
    arrowhead(QPointF , QGraphicsItem *, QGraphicsItem *, QGraphicsScene *); //QGraphicsLineItem *
private:
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;

    //void setMyLine(QGraphicsLineItem *newLine){myLine = newLine;}

    int type() const {return myAHType;}

    QGraphicsLineItem *myLine;

    AHType myAHType;

};

#endif // ARROWHEAD_H
