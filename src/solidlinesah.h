#ifndef SOLIDLINESAH_H
#define SOLIDLINESAH_H
#include "linebody.h"

class solidlineSAH : public lineBody
{
public:
    solidlineSAH(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDLINESAH_H
