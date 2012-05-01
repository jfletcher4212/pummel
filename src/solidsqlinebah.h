#ifndef SOLIDSQLINEBAH_H
#define SOLIDSQLINEBAH_H
#include "linebody.h"

class solidsqlinebah : public lineBody
{
public:
    solidsqlinebah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqlinebah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDSQLINEBAH_H
