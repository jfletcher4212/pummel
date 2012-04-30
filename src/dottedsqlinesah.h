#ifndef DOTTEDSQLINESAH_H
#define DOTTEDSQLINESAH_H
#include "linebody.h"

class dottedsqlinesah : public lineBody
{
public:
    dottedsqlinesah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedsqlinesah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    dottedsqlinesah(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // DOTTEDSQLINESAH_H
