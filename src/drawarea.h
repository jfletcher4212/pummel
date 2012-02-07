/*
 * DrawArea Widget
 * Uses DragScene, DragView, and DragItem
 *
 */


#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QtGui>
#include <QWidget>
#include "dragscene.h"
#include "dragview.h"

class DrawArea : public QWidget
{
    Q_OBJECT

public:
    DrawArea(QWidget *parent = 0, int newHeight = 250, int newWidth = 250); // specifies height/width for the DrawArea to create
    DragScene *scene;

private:

    DragView *view;
    QHBoxLayout *layout;

};

#endif // DRAWAREA_H
