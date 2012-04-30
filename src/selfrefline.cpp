#include "selfrefline.h"

const qreal Pi = 3.14;

selfRefLine::selfRefLine(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Self_Ref_Line;
}

selfRefLine::selfRefLine(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
}

selfRefLine::selfRefLine(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Self_Ref_Line;
}

void selfRefLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if(m_SourceReferenceObj != m_DestinationReferenceObj)
    {
        return;
    }
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF circleCenter = findSRLCenter(m_SourceReferenceObj);

    qreal radiusy = calcSRRadius(m_SourceReferenceObj);
    qreal radiusx = radiusy;

    QPointF arrowP1 = calcSRArrowPoint(circleCenter, radiusy);

    makeArrowHead(0, arrowP1);

    painter->drawEllipse(circleCenter, radiusx, radiusy);

    painter->setBrush(Qt::black);

    painter->drawPolygon(m_ArrowHead);

    update();
}
