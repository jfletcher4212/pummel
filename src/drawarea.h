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
    bool getSceneCreate(){return scene->getSceneCreate();}
    bool getSceneGrid(){return scene->getGrid();}
    int getSceneGridSize(){return scene->getGridSize();}
    QList<Icon*> getObjects(){return scene->getObjectList();}
    bool getLineCreate();

    // Mutators
    void setLineCreateType(LineType newType);
    void setLineCreate(bool a);
    void setSceneCreate(bool a){scene->setSceneCreate(a);}
    void setSceneGrid(bool a){scene->setGrid(a);}
    void setSceneGridSize(int newSize){scene->setGridSize(newSize);}
    DragScene *scene;

    // Testing
    void testAction(){scene->testAction();}

private:
    DragView *view;
    QHBoxLayout *layout;

};

#endif // DRAWAREA_H
