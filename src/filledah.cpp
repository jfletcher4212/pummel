#include "filledah.h"

const qreal Pi = 3.14;

filledAH::filledAH(QGraphicsLineItem *newLine, QGraphicsItem *parent, QGraphicsScene *scene) : arrowhead(newLine, parent, scene)
{
    parent = 0;
    scene = 0;
    myAHType = Solid_AH;
}

void filledAH:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double angle = line().angle();
    qreal arrowSize = 20;

    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::black);

    //The following lines are used to draw the arrowhead.
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawPolygon(arrowHead);
    //QPolygonF arrowHead;
}
