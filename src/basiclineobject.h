#ifndef BASICLINEOBJECT_H
#define BASICLINEOBJECT_H
#include <QGraphicsLineItem>
#include <QPen>
#include "icon.h"
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

/*
 * Is used when identifying custom items.
 * The default is UserType (65536) and the custom
 * item's enum value must be higher than or equal
 * to that.
 */

class BasicLineObject : public QGraphicsLineItem
{
public:
    //Constructor for the object
    BasicLineObject(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    //Overrides the default boundingRect() method inherited
    //from QGraphicsLineItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    //Methods for accessing the object's
    //various elements
    //int type() const
    //    { return Solid_Line; }
    virtual int type() const = 0;

    QColor setColor() const
        { return myColor; }
    //void updatePosition();
private:
protected:
    void swapLineDirection();


    double getAngle (QPointF, Icon *);//BasicLineObject line);

    QColor myColor;
    QPolygonF arrowHead;
};
#endif // BASICLINEOBJECT_H
