#include "arrowhead.h"

arrowhead::arrowhead(QGraphicsItem *parent, QGraphicsScene *scene) : BasicLineObject(parent, scene)
{
    parent = 0;
    scene = 0;

    //setMyLine(myLine);
    //this->setLine(QLineF(interPoint, initRefObj->pos()));
    //this->setLine(*myLine);
}
