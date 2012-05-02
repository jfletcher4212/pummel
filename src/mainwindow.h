#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "global.h"
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
    void deleteObj();
    void deleteSelected();
    void newTab();
    void newTab(QString filename, QList<Icon*> item_list, QList<lineBody*> line_list, QString d_type);
    void saveAsFile();
    void saveFile();
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
    void exit();
    // MVC logic methods
    //void write_xml(Icon **icon_list, int size, QString filename);
    

private:

    QWidget *widget;
    BorderLayout *layout;

    int next_tab_num;


    void createActions();
    void createMenus();
    
    // helper for xml reading
    QMap<QString, QString> parsePerson(QXmlStreamReader& xml);

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QMenu *objectsMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *closeAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *openAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *deleteObjAct;
    QAction *deleteSelectedAct;
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

    QLabel *infoLabel;
};

#endif
