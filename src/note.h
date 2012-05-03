#ifndef NOTE_H
#define NOTE_H

#include "icon.h"
#include "textboxdialog.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QImage>
#include "markerbox.h"

class Note : public Icon
{


protected:
    QRectF boundingRect() const;    //sets a reference rectangle to contain it
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

private:

    void arrangeBoxes();

public:

    Note(QPointF = QPointF(0,0), QGraphicsItem *parent = 0);
    Note(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label);

};

#endif // NOTE_H
