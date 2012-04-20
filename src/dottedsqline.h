#ifndef DOTTEDSQLINE_H
#define DOTTEDSQLINE_H

#include "linebody.h"

class dottedsqline : public lineBody
{
public:
    dottedsqline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    ~dottedsqline();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DOTTEDSQLINE_H
