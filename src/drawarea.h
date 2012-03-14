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
#include "basiclineobject.h"

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
    QList<DragItem*> getObjects();
    bool getLineCreate();

    // Mutators
    void setSceneCreateMode(ShapeType newType);

    void setLineCreateType(LineType newType);
    void setLineCreate(bool a);

    void setSceneCreate(bool a);
    void setSceneGrid(bool a);
    void setSceneGridSize(int newSize);
    DragScene *scene;

    // Testing

    void testAction();

private:
    DragView *view;
    QHBoxLayout *layout;

};

#endif // DRAWAREA_H
