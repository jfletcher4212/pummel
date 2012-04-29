#ifndef DOTTEDLINESD_H
#define DOTTEDLINESD_H
#include "linebody.h"

class dottedlineSD : public lineBody
{
public:
    dottedlineSD(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlineSD(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINESD_H
