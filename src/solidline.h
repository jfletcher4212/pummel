#ifndef SOLIDLINE_H
#define SOLIDLINE_H
#include "linebody.h"

class solidline : public lineBody
{
public:
   solidline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);

protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
#endif // SOLIDLINE_H
