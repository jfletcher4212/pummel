#ifndef SENARIOSTATE_H
#define SENARIOSTATE_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>

#include "markerbox.h"

class SenarioState : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:

    void arrangeBoxes();

public:

    SenarioState(QGraphicsItem *parent = 0);
    SenarioState(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label);

};

#endif // SENARIOSTATE_H
