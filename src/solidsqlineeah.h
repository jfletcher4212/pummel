#ifndef SOLIDSQLINEEAH_H
#define SOLIDSQLINEEAH_H
#include "linebody.h"

class solidsqlineeah : public lineBody
{
public:
    solidsqlineeah(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDSQLINEEAH_H
