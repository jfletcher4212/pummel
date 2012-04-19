#ifndef LINEBODY_H
#define LINEBODY_H

#include "basiclineobject.h"
#include <QPolygonF>

enum LineType {No_Line, Solid_Line, Dotted_Line, Solid_Line_SAH, Solid_Square_Line};

class lineBody : public BasicLineObject
{
public:
    lineBody(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    ~lineBody();

    Icon *sourceReferenceObj() const
        { return mySourceReferenceObj; }
    Icon *destinationReferenceObj() const
        { return myDestinationReferenceObj; }
    int type() const
            { return myLineType; }
    QPointF findIntersection (Icon *, QLineF);

private:

protected:

    void swapLineDirection();

    //QPointF findIntersection (Icon *, QLineF); //Find the intersection of the line and object, for determining arrow direction

    double getAngle (QPointF, Icon *);//BasicLineObject line);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)=0;

    //void updatePosition();

    Icon *mySourceReferenceObj;
    Icon *myDestinationReferenceObj;

    QPolygonF myPolygon;

    LineType myLineType;
};

#endif // LINEBODY_H
