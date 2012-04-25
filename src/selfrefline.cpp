#include "selfrefline.h"

const qreal Pi = 3.14;

selfRefLine::selfRefLine(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
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

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    int offset = 5;

    QPointF circleCenter = findObjectCenter(m_SourceReferenceObj);

    qreal radiusy = ((m_SourceReferenceObj->getHeight()) / 2 ) - offset;
    qreal radiusx = radiusy;

    QPointF arrowP1 = circleCenter;
    arrowP1.ry() += radiusy;

    double angle = 0;
    qreal arrowSize = 20;

    QPointF arrowP2 = arrowP1 + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP3 = arrowP1 + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);

    m_ArrowHead.clear();
    m_ArrowHead << arrowP1 << arrowP2 << arrowP3;

    painter->drawEllipse(circleCenter, radiusx, radiusy);

    painter->setBrush(Qt::black);

    painter->drawPolygon(m_ArrowHead);

    update();
}
