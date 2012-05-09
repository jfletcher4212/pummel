#ifndef SOLIDLINEBAH_H
#define SOLIDLINEBAH_H
#include "linebody.h"

class solidlineBAH : public lineBody
{
public:
    //Constructors
    solidlineBAH(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    solidlineBAH(Icon *, Icon *, int,  int, QGraphicsItem *, QGraphicsScene *);
    solidlineBAH(int id_start, int id_end);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // SOLIDLINEBAH_H
