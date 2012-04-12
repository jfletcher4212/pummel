#ifndef DOTTEDLINE_H
#define DOTTEDLINE_H
#include "linebody.h"

class dottedline : public lineBody
{
public:
    dottedline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
private:
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDLINE_H
