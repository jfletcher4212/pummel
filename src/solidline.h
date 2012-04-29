#ifndef SOLIDLINE_H
#define SOLIDLINE_H
#include "linebody.h"

class solidline : public lineBody
{
public:
   solidline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
   solidline(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
   solidline(int id_start, int id_end);

protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
#endif // SOLIDLINE_H
