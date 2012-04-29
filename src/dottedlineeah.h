#ifndef DOTTEDLINEEAH_H
#define DOTTEDLINEEAH_H
#include "linebody.h"

class dottedlineeah : public lineBody
{
public:
    dottedlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlineeah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINEEAH_H
