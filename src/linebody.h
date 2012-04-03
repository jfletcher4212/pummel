#ifndef LINEBODY_H
#define LINEBODY_H

#include "basiclineobject.h"

enum LineType {Solid_Line};

class lineBody : public BasicLineObject
{
public:
    lineBody(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);

    Icon *sourceReferenceObj() const
        { return mySourceReferenceObj; }
    Icon *destinationReferenceObj() const
        { return myDestinationReferenceObj; }
    int type() const
            { return Solid_Line; }
private:

protected:

    QPointF findIntersection (Icon *, QLineF); //Find the intersection of the line and object, for determining arrow direction

    Icon *mySourceReferenceObj;
    Icon *myDestinationReferenceObj;
};

#endif // LINEBODY_H
