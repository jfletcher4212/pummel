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

private:

    int width;
    int height;

};

#endif // MARKERBOX_H
