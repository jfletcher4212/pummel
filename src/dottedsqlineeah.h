#ifndef DOTTEDSQLINEEAH_H
#define DOTTEDSQLINEEAH_H
#include "linebody.h"

class dottedsqlineeah : public lineBody
{
public:
    //Constructors
    dottedsqlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedsqlineeah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    dottedsqlineeah(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDSQLINEEAH_H
