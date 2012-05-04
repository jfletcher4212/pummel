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

enum LineType {No_Line, Solid_Line, Dotted_Line, Solid_Line_SAH, Dotted_Line_SAH, Solid_Line_EAH, Dotted_Line_EAH, Solid_Line_SD, Dotted_Line_SD, Solid_Line_ED, Dotted_Line_ED, Solid_Line_BAH, Dotted_Line_BAH, Solid_Square_Line, Dotted_Square_Line, Solid_Sq_Line_SAH, Dotted_Sq_Line_SAH, Solid_Sq_Line_EAH, Dotted_Sq_Line_EAH, Self_Ref_Line, Solid_Sq_Line_BAH, Solid_Sq_Line_SD, Solid_Sq_Line_ED};

class lineBody : public QGraphicsLineItem
{
public:
    friend class ut_lineBody;
	lineBody(Icon *, Icon *, QGraphicsItem *, QGraphicsScene *);
    lineBody(Icon *, Icon *, int, int, QGraphicsItem *, QGraphicsScene *);
    lineBody(int, int);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    //accessors
    Icon *getSourceReferenceObj() const
        { return m_SourceReferenceObj; }
    Icon *getDestinationReferenceObj() const
        { return m_DestinationReferenceObj; }
    int getLinetype() const
        { return m_LineType; }
    int get_id_start() const
        { return m_Id_Start; }
    int get_id_end() const
        { return m_Id_End; }
    QColor getColor() const
        { return m_Color; }

    //mutators
    void set_ids(int id_start, int id_end)
        { m_Id_Start = id_start; m_Id_End = id_end; }
    void set_id_start(int id)
        { m_Id_Start = id; }
    void set_id_end(int id)
        { m_Id_End = id; }
    void setSourceObject(Icon* newSource)
        { m_SourceReferenceObj = newSource; }
    void setDestObject(Icon *newDest)
        { m_DestinationReferenceObj = newDest; }

protected:


    Icon *m_SourceReferenceObj;
    Icon *m_DestinationReferenceObj;
    LineType m_LineType;
    QColor m_Color;
    QPolygonF m_ArrowHead;
    int m_Id_Start;
    int m_Id_End;

    double getAngle ();
    QPointF findIntersection (Icon *, QLineF);
    QPointF findObjectCenter(Icon *);
    QPointF findSRLCenter(Icon *);
    qreal calcSRRadius(Icon *);
    QPointF calcSRArrowPoint(QPointF, qreal);
    void squareLine(qreal, QPointF, QPointF, QPointF *, QPointF *);

    bool checkReferences(Icon *, Icon *);
    bool checkInterPoint(QPointF);

    void bareArrowHead(double, QLineF, QPointF *, QPointF *);
    void makeArrowHead(double, QPointF);
    void makeArrowHead(double, QLineF);
    void makeDiamond(double, QLineF);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)=0;
};

#endif // LINEBODY_H
