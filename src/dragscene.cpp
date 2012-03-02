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
    connectMode = false;
    pen = new QPen();
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

void DragScene::setSceneCreate(bool a){
    sceneCreate = a;
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

bool DragScene::getSceneConnect(){
    return connectMode;
}

void DragScene::setSceneConnect(bool a){
    connectMode = a;
}

void DragScene::addSceneConnection(DragItem* a, DragItem* b){
    Connection* newConnect = new Connection();
    newConnect->setObjects(a, b);
    connection_list.append(newConnect);
}

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // this block checks if an object is under the cursor, if so, select it
    int topItem = 0;
    if(this->itemAt(event->scenePos())){
        int index;
        // object bounds checking shenanigans below
        for(int i = 0; i < scene_items.size(); i++){
            if((int)event->scenePos().x() >= (int)scene_items.at(i)->x() &&
                     (int)event->scenePos().x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                     (int)event->scenePos().y() >= (int)scene_items.at(i)->y() &&
                     (int)event->scenePos().y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight()))){
                if(scene_items.at(i)->zValue() > topItem){
                    topItem = scene_items.at(i)->zValue(); // ensures the top item is selected, not the ones below it
                    index = i;
                }
            }
        }
        DragItem *item = scene_items.at(index);
        // if there are items selected, this will deselect them
        for(int i = 0; i < scene_items.size(); i++){
            scene_items.at(i)->setSelected(false);
        }
        item->setSelected(true);
    } else if(this->selectedItems().size() == 0 && sceneCreate){
        // if there is no object under the cursor, the number of selected items is zero,and sceneCreate is true, create an new item
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
                printf("Error in DragScene::mouseDoubleClickEvent, Why doesn't the scene have a static createMode set?\n");
                exit(1);
            }
        }
        this->addItem(newItem);
        newItem->setPos(event->scenePos());
        scene_items.append(newItem);
        }
    // connections
    if(connectMode && this->itemAt(event->scenePos())){
        int selectedIndex, eventIndex;
        // find selected item
        for(int i = 0; i < scene_items.size(); i++){
            if(scene_items.at(i)->isSelected()){
                selectedIndex = i;
            }
        }

        // find event item
        int topItem = 0;
        for(int i = 0; i < scene_items.size(); i++){
            if((int)event->scenePos().x() >= (int)scene_items.at(i)->x() &&
                     (int)event->scenePos().x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                     (int)event->scenePos().y() >= (int)scene_items.at(i)->y() &&
                     (int)event->scenePos().y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight()))){
                if(scene_items.at(i)->zValue() > topItem){
                    topItem = scene_items.at(i)->zValue(); // ensures the top item is selected, not the ones below it
                    eventIndex = i;
                }
            }
        }
        // add connection

        addSceneConnection(scene_items.at(selectedIndex), scene_items.at(eventIndex));
        printf("added connection\n");
        connectMode = false;
    }
    update();
    QGraphicsScene::mousePressEvent(event);
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseMoveEvent(event);
}

void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    DragItem* lastItem;
    for(int i = 0; i < scene_items.size(); i++){
        if(scene_items.at(i)->getState() == 2){
            scene_items.at(i)->setState(1);
            lastItem = scene_items.at(i);
        } else{
            scene_items.at(i)->setState(0);
        }
    }

    if(this->itemAt(event->scenePos())){
        int maxZ = 0;
        for(int i = 0; i < scene_items.size(); i++){
            if((int)event->scenePos().x() >= (int)scene_items.at(i)->x() &&
                     (int)event->scenePos().x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                     (int)event->scenePos().y() >= (int)scene_items.at(i)->y() &&
                     (int)event->scenePos().y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight()))){
                if(scene_items.at(i)->zValue() > maxZ){
                    maxZ = scene_items.at(i)->zValue();
                }
            }
        }
        lastItem->setZValue(maxZ+1);
    }
    update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void DragScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    for(int i = 0; i < connection_list.size(); i++){
        this->addLine(connection_list.at(i)->getStartObject()->x(), connection_list.at(i)->getStartObject()->y(), connection_list.at(i)->getEndObject()->x(), connection_list.at(i)->getStartObject()->y(), *pen);

    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void DragScene::drawBackground(QPainter *painter, const QRectF &rect){
    // if the grid is on, draw the background
    if(grid){
        int gridInterval = gridSize; //interval to draw grid lines at
        painter->setWorldMatrixEnabled(true);
        qreal left = int(rect.left()) - (int(rect.left()) % gridInterval );
        qreal top = int(rect.top()) - (int(rect.top()) % gridInterval );
        QVarLengthArray<QLineF, 100> linesX;
        for (qreal x = left; x < rect.right(); x += gridInterval ){
            linesX.append(QLineF(x, rect.top(), x, rect.bottom()));
        }
        QVarLengthArray<QLineF, 100> linesY;
        for (qreal y = top; y < rect.bottom(); y += gridInterval ){
            linesY.append(QLineF(rect.left(), y, rect.right(), y));
        }
        painter->setOpacity(0.2);
        painter->drawLines(linesX.data(), linesX.size());
        painter->drawLines(linesY.data(), linesY.size());
    }
}


void DragScene::testAction(){
    DragItem* item1 = new DragItem();
    DragItem* item2 = new DragItem();
    item1 = scene_items.at(0);
    item2 = scene_items.at(1);
    addSceneConnection(scene_items.at(0), scene_items.at(1));
    item1 = scene_items.at(1);
    item2 = scene_items.at(2);
    addSceneConnection(scene_items.at(1), scene_items.at(2));
    item1 = scene_items.at(3);
    item2 = scene_items.at(4);
    addSceneConnection(scene_items.at(3), scene_items.at(4));
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





