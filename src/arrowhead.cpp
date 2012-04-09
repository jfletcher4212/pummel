#include "arrowhead.h"

arrowhead::arrowhead(QGraphicsLineItem *newLine, QGraphicsItem *parent, QGraphicsScene *scene) : BasicLineObject(parent, scene)
{
    parent = 0;
    scene = 0;

    setMyLine(newLine);
}
