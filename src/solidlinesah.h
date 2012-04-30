#ifndef SOLIDLINESAH_H
#define SOLIDLINESAH_H
#include "linebody.h"

class solidlineSAH : public lineBody
{
public:
    solidlineSAH(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidlineSAH(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    solidlineSAH(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    //void mousePressEvent(QGraphicsSceneMouseEvent *);
};

#endif // SOLIDLINESAH_H
