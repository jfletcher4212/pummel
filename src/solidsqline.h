#ifndef SQUARELINE_H
#define SQUARELINE_H

#include "linebody.h"

class solidsqline : public lineBody
{
public:
    solidsqline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidsqline(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SQUARELINE_H
