#include "arrowhead.h"

arrowhead::arrowhead(QPointF interPoint, QGraphicsItem *initRefObj, QGraphicsItem *parent, QGraphicsScene *scene) : BasicLineObject(parent, scene)
{
    parent = 0;
    scene = 0;

    //setMyLine(newLine);
    this->setLine(QLineF(interPoint, initRefObj->pos()));
}
