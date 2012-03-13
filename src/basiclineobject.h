#ifndef BASICLINEOBJECT_H
#define BASICLINEOBJECT_H
#include <QGraphicsLineItem>
#include <QPen>
#include "dragitem.h"
#include <QtGui>
QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class QPointF;
QT_END_NAMESPACE

//Is used when identifying custom items.
//The default is UserType (65536) and the custom
//item's enum value must be higher than or equal
//to that.
//References: QGraphicsItem::type()
//T qgraphicsitem_cast
//enum { objType = UserType + 4 };
enum LineType {Solid_Line};

class BasicLineObject : public QGraphicsLineItem
{
public:
    //Constructor for the object
    BasicLineObject(DragItem *sourceReferenceObj, DragItem *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    //Overrides the default boundingRect() method inherited
    //from QGraphicsLineItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    //Methods for accessing the object's
    //various elements
    int type() const
        { return Solid_Line; } //objType; }
    DragItem *sourceReferenceObj() const
        { return mySourceReferenceObj; }
    DragItem *destinationReferenceObj() const
        { return myDestinationReferenceObj; }
    QColor setColor() const
        { return myColor; }
    //void updatePosition();
private:
protected:
    void swapLineDirection();
    QPointF findIntersection (DragItem *, QLineF); //Find the intersection of the line and object, for determining arrow direction
    double getAngle (QPointF, DragItem *);//BasicLineObject line);
    DragItem *mySourceReferenceObj;
    DragItem *myDestinationReferenceObj;
    QColor myColor;
    QPolygonF arrowHead;
    //const LineType typeOfLine_ = Solid_Line;
};
#endif // BASICLINEOBJECT_H
