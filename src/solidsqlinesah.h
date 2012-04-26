#ifndef SOLIDSQLINESAH_H
#define SOLIDSQLINESAH_H
#include "linebody.h"

class solidsqlinesah : public lineBody
{
public:
    solidsqlinesah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDSQLINESAH_H
