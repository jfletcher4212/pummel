#ifndef DOTTEDLINESAH_H
#define DOTTEDLINESAH_H
#include "linebody.h"

class dottedlineSAH : public lineBody
{
public:
    dottedlineSAH(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    dottedlineSAH(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDLINESAH_H
