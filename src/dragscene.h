/*
 * Reimplementation of QGraphicsScene
 * Manages DragItems
 *
 */

#ifndef DRAGSCENE_H
#define DRAGSCENE_H

#include <QtGui>
#include <QGraphicsScene>
#include "dragitem.h"

class DragScene : public QGraphicsScene
{
public:
    /*
      DragScene constructor, default size of the scene is 500x500, can be set to whatever we want, most likely
      we will want to scale it with window size.
      */

    DragScene(QObject* parent = 0, int initHeight = 500, int initWidth = 500);
    void setCreateMode(ShapeType newType);
    ShapeType getCreateMode();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    ShapeType createMode;


};

#endif // DRAGSCENE_H
