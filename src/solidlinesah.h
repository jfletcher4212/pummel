#ifndef SOLIDLINESAH_H
#define SOLIDLINESAH_H
#include "linebody.h"

class solidlineSAH : public lineBody
{
public:
    solidlineSAH(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidlineSAH(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    //void mousePressEvent(QGraphicsSceneMouseEvent *);
};

#endif // SOLIDLINESAH_H
