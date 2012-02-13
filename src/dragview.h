/*
 * Reimplementation of QGraphicsView
 * Displays DragScene
 *
 */

#ifndef DRAGVIEW_H
#define DRAGVIEW_H

#include <QtGui>
#include <QGraphicsView>

class DragView : public QGraphicsView
{
public:
    DragView(QWidget *parent = 0);
};

#endif // DRAGVIEW_H
