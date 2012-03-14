#include "dragscene.h"
#include "dragitem.h"

#include <QList>
#include <QGraphicsSceneDragDropEvent>
#include <QXmlStreamWriter>
#include <QIODevice>

DragScene::DragScene(QObject* parent, int initHeight, int initWidth){
    parent = 0;
    this->setSceneRect(QRectF(0,0,initHeight, initWidth));
    createMode = Square;
    sceneCreate = false;
    gridSize = 10;
    grid = true;
}

void DragScene::setCreateMode(ShapeType newType){
    createMode = newType;
}

ShapeType DragScene::getCreateMode(){
    return createMode;
}

QList<DragItem*> DragScene::getObjectList(){
    return scene_items;
}

bool DragScene::getSceneCreate(){
    return sceneCreate;
}

bool DragScene::getLineCreate(){
    return lineCreate;
}

LineType DragScene::getLineCreateType()
{
   return lineTypeEnum;
}

void DragScene::setSceneCreate(bool a){
    sceneCreate = a;
}

void DragScene::setLineCreateType(LineType newType)
{
    lineTypeEnum = newType;
}

void DragScene::setLineCreate(bool a)
{
   lineCreate = a;
}

void DragScene::setGrid(bool a){
    grid = a;
    update();
}

void DragScene::setGridSize(int newSize){
    gridSize = newSize;
    update();
}

bool DragScene::getGrid(){
    return grid;
}

int DragScene::getGridSize(){
    return gridSize;
}

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // this block checks if an object is under the cursor, if so, select it
    int topItem = -1;
    int index = -1; // left at -1 to make sure an object is clicked, not a markerbox
    if(this->itemAt(event->scenePos())){
        // object bounds checking shenanigans below
        for(int i = 0; i < scene_items.size(); i++)
        {
            if((int)event->scenePos().x() >= (int)scene_items.at(i)->x() &&
                    (int)event->scenePos().x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                    (int)event->scenePos().y() >= (int)scene_items.at(i)->y() &&
                    (int)event->scenePos().y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight())))
            {
                if(scene_items.at(i)->zValue() > topItem)
                {
                    topItem = scene_items.at(i)->zValue(); // ensures the top item is selected, not the ones below it
                    index = i;
                }
            }
        }
        // if still -1, clicked a marker box
        if(index < 0){
            // do nothing
        } else {
            DragItem *item = scene_items.at(index);
            // if there are items selected, this will deselect them
            for(int i = 0; i < scene_items.size(); i++)
            {
                scene_items.at(i)->setSelected(false);
            }
            // selected the last clicked item
            item->setSelected(true);

            //Learn if in line creation mode
            if (lineCreate == true)
            {

            }
        }


    }
    else if(this->selectedItems().size() == 0 && sceneCreate){
        // if there is no object under the cursor, the number of selected items is zero,and sceneCreate is true, create a new item
        DragItem *newItem = new DragItem();
        newItem->setShape(createMode);
        switch(createMode){
        case Square:{
            newItem->setSize(25, 25);
            break;
        }
        case Rectangle:{
            newItem->setSize(60, 25);
            break;
        }
        case Circle:{
            newItem->setSize(25, 25);
            break;
        }
        case Ellipse:{
            newItem->setSize(60, 25);
            break;
        }
        default:{
            printf("Error in DragScene::mousePressEvent, Why doesn't the scene have a static createMode set?\n");
            exit(1);
        }
        }
        // add the new item to the scene
        this->addItem(newItem);
        newItem->setPos(event->scenePos());
        // add new item to the custom list
        scene_items.append(newItem);
    }
    update();
    QGraphicsScene::mousePressEvent(event);
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseMoveEvent(event);
}

void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    DragItem* lastItem;
    // find what the last item dropped (state 2), set it to state 1, reset everything else (state 0)
    for(int i = 0; i < scene_items.size(); i++){
        if(scene_items.at(i)->getState() == 2){
            scene_items.at(i)->setState(1);
            lastItem = scene_items.at(i);
        } else{
            scene_items.at(i)->setState(0);
        }
    }

    if(this->itemAt(event->scenePos())){
        // starting at -1 forces the loop to run
        int maxZ = -1;
        int index = -1;
        for(int i = 0; i < scene_items.size(); i++){
            if((int)event->scenePos().x() >= (int)scene_items.at(i)->x() &&
                    (int)event->scenePos().x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                    (int)event->scenePos().y() >= (int)scene_items.at(i)->y() &&
                    (int)event->scenePos().y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight()))){
                if(scene_items.at(i)->zValue() > maxZ){
                    index = i;
                    maxZ = scene_items.at(i)->zValue();
                }
            }
        }
        // marker box check
        if(index < 0){
            // clicked a markerbox
        }
        else {
            // increment the zValue
            lastItem->setZValue(maxZ+1);
        }
    }
    update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void DragScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void DragScene::drawBackground(QPainter *painter, const QRectF &rect){
    // if the grid is on, draw the background
    if(grid){
        int gridInterval = gridSize; //interval to draw grid lines at
        painter->setWorldMatrixEnabled(true);
        // find the start points
        qreal left = int(rect.left()) - (int(rect.left()) % gridInterval );
        qreal top = int(rect.top()) - (int(rect.top()) % gridInterval );
        QVarLengthArray<QLineF, 100> linesX;
        // create all the lines for background
        // X lines
        for (qreal x = left; x < rect.right(); x += gridInterval ){
            linesX.append(QLineF(x, rect.top(), x, rect.bottom()));
        }
        // Y lines
        QVarLengthArray<QLineF, 100> linesY;
        for (qreal y = top; y < rect.bottom(); y += gridInterval ){
            linesY.append(QLineF(rect.left(), y, rect.right(), y));
        }
        // paint them, opacity is 20%
        painter->setOpacity(0.2);
        painter->drawLines(linesX.data(), linesX.size());
        painter->drawLines(linesY.data(), linesY.size());
    }
}


void DragScene::testAction(){

}
/*
void DragScene::writeXML(QString *filename)
{
    int i;
    QFile *file = new QFile(filename);
    QXmlStreamWriter *writer = new QXmlStreamWriter(file);
    
    writer->writeStartDocument();
    
    writer->writeEndDocument();
    
    file.close();
    
    delete file;
    delete writer;
}
    */





