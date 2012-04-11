#include "tabmanager.h"
#include "global.h"
#include "mainwindow.h"
extern MainWindow window;
extern Toolbar *toolbar;

TabManager::TabManager(QWidget *parent) : QTabWidget(parent)
{
    connect(this , SIGNAL(currentChanged(int)),this,SLOT(currentChangedSlot(int)));
}


void TabManager::currentChangedSlot(int index)
{
    DiagramType t = canvas.at(tabWidget->currentIndex())->getDiagramType();
    ShapeCreationType s = canvas.at(tabWidget->currentIndex())->scene->getShapeCreationType();
    LineType l = canvas.at(tabWidget->currentIndex())->scene->getLineCreateType();

    toolbar->canvasSync(t,s, l);
}

