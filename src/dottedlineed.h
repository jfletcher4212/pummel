#ifndef DOTTEDLINEED_H
#define DOTTEDLINEED_H
#include "linebody.h"

class dottedlineed : public lineBody
{
public:
    dottedlineed(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlineed(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINEED_H
