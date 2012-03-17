#ifndef MARKERBOX_H
#define MARKERBOX_H

#include <QtGui>
#include <QGraphicsItem>

class MarkerBox : public QGraphicsItem
{
public:
    MarkerBox(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // Mutators
    void setId(int x){id = x;};

private:
    int itemIndex;
    int id;
    int startX;
    int startY;

    int width;
    int height;

};

#endif // MARKERBOX_H
