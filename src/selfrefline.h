#ifndef SELFREFLINE_H
#define SELFREFLINE_H

#include "linebody.h"

class selfRefLine : public lineBody
{
public:
    selfRefLine(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    selfRefLine(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SELFREFLINE_H
