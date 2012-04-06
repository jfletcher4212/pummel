

#ifndef SOLIDLINE_H
#define SOLIDLINE_H
//#include "basiclineobject.h"
#include "linebody.h"

//class solidline : public BasicLineObject
class solidline : public lineBody
{
public:
    //enum { objType = UserType + 6 };
   // solidline(DragItem *sourceReferenceObj, DragItem *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
   solidline(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
private:

protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
#endif // SOLIDLINE_H
