#ifndef DOTTEDLINEEAH_H
#define DOTTEDLINEEAH_H
#include "linebody.h"

class dottedlineeah : public lineBody
{
public:
    dottedlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlineeah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    dottedlineeah(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINEEAH_H
