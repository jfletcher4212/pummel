#ifndef FILLEDAH_H
#define FILLEDAH_H
#include "arrowhead.h"

class filledAH : public arrowhead
{
public:
    filledAH(QGraphicsLineItem *, QGraphicsItem *, QGraphicsScene *);
private:
protected:
    QGraphicsItem *fillerItem;
    QPointF fillerPoint;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // FILLEDAH_H
