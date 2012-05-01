#ifndef SCENARIOEND_H
#define SCENARIOEND_H

#include "icon.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"
class ScenarioEnd : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

public:

    ScenarioEnd(QGraphicsItem *parent = 0);
    ScenarioEnd(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos);

};

#endif // SCENARIOEND_H
