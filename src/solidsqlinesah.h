#ifndef SOLIDSQLINESAH_H
#define SOLIDSQLINESAH_H
#include "linebody.h"

class solidsqlinesah : public lineBody
{
public:
    solidsqlinesah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqlinesah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    solidsqlinesah(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDSQLINESAH_H
