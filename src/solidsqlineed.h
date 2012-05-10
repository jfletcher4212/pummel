#ifndef SOLIDSQLINEED_H
#define SOLIDSQLINEED_H
#include "linebody.h"

class solidsqlineed : public lineBody
{
public:
    //Constructors
    solidsqlineed(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqlineed(int id_start, int id_end);
    solidsqlineed(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDSQLINEED_H
