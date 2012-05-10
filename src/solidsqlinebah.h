#ifndef SOLIDSQLINEBAH_H
#define SOLIDSQLINEBAH_H
#include "linebody.h"

class solidsqlinebah : public lineBody
{
public:
    //Constructors
    solidsqlinebah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqlinebah(int id_start, int id_end);
    solidsqlinebah(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDSQLINEBAH_H
