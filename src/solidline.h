

#ifndef SOLIDLINE_H
#define SOLIDLINE_H
#include "basiclineobject.h"


class solidline : public BasicLineObject
{
public:
    //enum { objType = UserType + 6 };
   // solidline(DragItem *sourceReferenceObj, DragItem *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
   solidline(DragItem *, DragItem *, QGraphicsItem *, QGraphicsScene *);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
protected:
};
#endif // SOLIDLINE_H
