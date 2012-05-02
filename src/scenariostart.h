#ifndef SCENARIOSTART_H
#define SCENARIOSTART_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class ScenarioStart : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

public:

    ScenarioStart(QPointF = QPointF(0,0), QGraphicsItem *parent = 0);
    ScenarioStart(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos);

};

#endif // SCENARIOSTART_H
