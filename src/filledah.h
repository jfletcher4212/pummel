#ifndef FILLEDAH_H
#define FILLEDAH_H
#include "arrowhead.h"

class filledAH : public arrowhead
{
public:
    filledAH(double, QGraphicsItem *, QGraphicsScene *);
private:
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    double myAngle;
};

#endif // FILLEDAH_H
