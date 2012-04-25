#ifndef DOTTEDSQLINEEAH_H
#define DOTTEDSQLINEEAH_H
#include "linebody.h"

class dottedsqlineeah : public lineBody
{
public:
    dottedsqlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    ~dottedsqlineeah();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // DOTTEDSQLINEEAH_H
