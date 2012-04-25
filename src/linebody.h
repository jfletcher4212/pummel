#ifndef LINEBODY_H
#define LINEBODY_H

//#include "basiclineobject.h"
#include <QPolygonF>
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

enum LineType {No_Line, Solid_Line, Dotted_Line, Solid_Line_SAH, Dotted_Line_SAH, Solid_Line_EAH, Dotted_Line_EAH, Solid_Line_SD, Dotted_Line_SD, Solid_Line_ED, Dotted_Line_ED, Solid_Line_BAH, Dotted_Line_BAH, Solid_Square_Line, Dotted_Square_Line, Solid_Sq_Line_SAH, Dotted_Sq_Line_SAH, Solid_Sq_Line_EAH, Dotted_Sq_Line_EAH, Self_Ref_Line};

class lineBody : public QGraphicsLineItem//: public BasicLineObject
{
public:
    lineBody(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    lineBody(int idx_start, int idx_end);
    ~lineBody();
    
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QColor setColor() const
        { return myColor; }

    Icon *sourceReferenceObj() const
        { return mySourceReferenceObj; }
    Icon *destinationReferenceObj() const
        { return myDestinationReferenceObj; }
    int type() const
            { return myLineType; }
    
    // index accessors
    int get_idx_start() { return m_idx_start; }
    int get_idx_end() { return m_idx_end; }

    // mutators
    void set_idxs(int idx_start, int idx_end) { m_idx_start = idx_start; m_idx_end = idx_end; }
    void set_idx_start(int idx) { m_idx_start = idx; }
    void set_idx_end(int idx) { m_idx_end = idx; }
    
    void setSourceObject(Icon* newSource);
    void setDestObject(Icon *newDest);
    QPointF findIntersection (Icon *, QLineF);

private:

protected:
    
    int m_idx_start;
    int m_idx_end;

    void swapLineDirection();

    //QPointF findIntersection (Icon *, QLineF); //Find the intersection of the line and object, for determining arrow direction

    double getAngle (QPointF, Icon *);//BasicLineObject line);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)=0;

    //void updatePosition();

    Icon *mySourceReferenceObj;
    Icon *myDestinationReferenceObj;

    QPolygonF myPolygon;

    LineType myLineType;

    QColor myColor;

    QPolygonF arrowHead;
};

#endif // LINEBODY_H
