#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include "drawarea.h"
#include "optionsdialog.h"
#include "borderlayout.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void newTab();
    void saveAsFile();
    void openFile();
    void closeTab();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();

    void addRect();
    void addEllipse();
    void addCircle();
    void addSquare();

private:

    QWidget *widget;

    Toolbar *toolbar;
    DrawArea *canvas;
    BorderLayout *layout;
    /*Tabs for multiple files open at once*/
    QTabWidget *tabWidget;
    QWidget *fileTab;


    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QMenu *objectsMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QActionGroup *objectsGroup;
    QAction *addSquareAct;
    QAction *addCircleAct;
    QAction *addRectAct;
    QAction *addEllipseAct;

    QLabel *infoLabel;
};

#endif
