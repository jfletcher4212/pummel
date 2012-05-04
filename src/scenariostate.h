#ifndef SCENARIOSTATE_H
#define SCENARIOSTATE_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"

class ScenarioState : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:

    void arrangeBoxes();

public:

    ScenarioState(QPointF = QPointF(0,0), QGraphicsItem *parent = 0);
    ScenarioState(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label);

};

#endif // SCENARIOSTATE_H
