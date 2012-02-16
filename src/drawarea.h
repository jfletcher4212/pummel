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
    // Constructor specifies height/width for the DrawArea to create
    DrawArea(QWidget *parent = 0, int newHeight = 250, int newWidth = 250);

    // Accessors
    ShapeType getSceneCreateMode();
    bool getSceneCreate();
    bool getSceneGrid();
    int getSceneGridSize();

    // Mutators
    void setSceneCreateMode(ShapeType newType);
    void setSceneCreate(bool a);
    void setSceneGrid(bool a);
    void setSceneGridSize(int newSize);
    DragScene *scene;

private:


    DragView *view;
    QHBoxLayout *layout;

};

#endif // DRAWAREA_H
