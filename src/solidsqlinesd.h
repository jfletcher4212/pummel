#ifndef SOLIDSQLINESD_H
#define SOLIDSQLINESD_H
#include "linebody.h"

class solidsqlinesd : public lineBody
{
public:
    //Constructors
    solidsqlinesd(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqlinesd(int id_start, int id_end);
    solidsqlinesd(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDSQLINESD_H
