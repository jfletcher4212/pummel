#ifndef DOTTEDLINEBAH_H
#define DOTTEDLINEBAH_H
#include "linebody.h"

class dottedlinebah : public lineBody
{
public:
    dottedlinebah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlinebah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINEBAH_H
