#ifndef SOLIDLINEEAH_H
#define SOLIDLINEEAH_H
#include "linebody.h"

class solidlineeah : public lineBody
{
public:
    solidlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidlineeah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDLINEEAH_H
