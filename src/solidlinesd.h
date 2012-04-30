#ifndef SOLIDLINESD_H
#define SOLIDLINESD_H
#include "linebody.h"

class solidlineSD : public lineBody
{
public:
    solidlineSD(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidlineSD(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    solidlineSD(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDLINESD_H
