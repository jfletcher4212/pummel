
#include <QtGui>

#include "mainwindow.h"
#include "borderlayout.h"
#include "global.h"
#include "xml_io.h"
#include <iostream>
#include <QFile>

using namespace std;

extern Toolbar *toolbar;

MainWindow::MainWindow()
{
    widget = new QWidget;
    setCentralWidget(widget);

    QIcon thumbnail;                    //this sets up an image for the upper corner
    thumbnail.addFile("icons/viking.png"); //while its running

    toolbar = new Toolbar;
    layout = new BorderLayout;
    /*Create tab objects*/
    tabWidget = new TabManager;
    next_tab_num = 1;
    /*end*/
    layout->setMargin(5);
    layout->addWidget(toolbar, BorderLayout::West);
    /*Add tab objects to mainwindow*/
    layout->addWidget(tabWidget, BorderLayout::Center);
    /*end*/
    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("pUML"));
    setWindowIcon(thumbnail);
    setMinimumSize(160, 160);
    resize(600, 500);
    this->newTab();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.addAction(deleteAct);
    menu.exec(event->globalPos());
}

void MainWindow::newFile()
{
    /* for some reason, this next line prevented the
     * project from working correctly (ie, it would
     * crash as soon as newFile() was called, even if
     * newTab() was commented out)*/
    //infoLabel->setText(tr("Invoked <b>File|New</b>"));
    newTab();
}

void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::print()
{
    infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void MainWindow::undo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::cut()
{
    // whatever this line is crashes it
    // infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));

    // Testing for connections below, I just needed something to click, will delete all of it
    canvas.at(tabWidget->currentIndex())->testAction();

}

void MainWindow::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::deleteObject()
{
    printf("items: %d\n", canvas.at(tabWidget->currentIndex())->scene->getObjectList().size());
    if(canvas.at(tabWidget->currentIndex())->scene->getObjectList().size() > 0){
        Icon* item;
        for(int i = 0; i < canvas.at(tabWidget->currentIndex())->scene->getObjectList().size(); i++)
        {
            if(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(i)->isSelected())
            {
                item = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(i);
            }
        }
        canvas.at(tabWidget->currentIndex())->scene->deleteItem(item);
        printf("items: %d\n", canvas.at(tabWidget->currentIndex())->scene->getObjectList().size());
    }
}

/*
 * Function for creating a new tab;
 * Should be invoked by new-file and open-file.
 *
 * For differentiating between unsaved and saved files,
 * perhaps a 'filename' argument should be passed in.
 *
 * The tabs and canvas have an index number when they are created, Tab 1 =  Canvas 1, etc.
 * This will only be a problem if someone makes huge amounts of Tabs (maybe... I don't know how well QList would handle it)
 * But it has been tested to handle about 20 tabs, any more than that seems overkill
 */

void MainWindow::newTab()
{
    int i = tabWidget->count();
    char* s = (char*)malloc(10*sizeof(char));
    sprintf(s, "untitled" );
    next_tab_num++;
    QString q = QString(s);
    DrawArea *newCanvas = new DrawArea;
    canvas.append(newCanvas);
    tabWidget->insertTab(i, newCanvas, s);
    tabWidget->setCurrentIndex(i);
    tabWidget->widget(i)->setVisible(true);
    free(s);
}
/*end*/
void MainWindow::newTab(QString filename)
{
    int i = tabWidget->count();
    char* s = (char*)malloc(10*sizeof(char));
    sprintf(s, "untitled" );
    next_tab_num++;
    QString q = QString(s);
    DrawArea *newCanvas = new DrawArea;
    canvas.append(newCanvas);
    tabWidget->insertTab(i, newCanvas, filename);
    tabWidget->setCurrentIndex(i);
    tabWidget->widget(i)->setVisible(true);
    free(s);
}
void MainWindow::saveFile()
{
    QString filename = tabWidget->tabText(tabWidget->currentIndex());
    if(filename == "untitled")
    {
        saveAsFile();
    }
    else
    {
    //writer.write_xml();
    }
}

void MainWindow::saveAsFile()
{
    // dialog box for user to enter filename
    QString filename = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "*.xml");
    if( filename == "" )
    {
        cout << "No filename given, writing anyways" << endl;
    }
    else
    {
    //Xml_io writer(icon_list, filename/*, diagram_type*/);
    
    // write the file
    //writer.write_xml();
    

    // strip full path off filename for display
    int idx = filename.lastIndexOf("/");
    filename.remove(0, idx+1);

    tabWidget->setTabText(tabWidget->currentIndex(), filename );
    }
}

void MainWindow::openFile()
{
<<<<<<< local
  QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
  newTab(filename);
=======
    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
    newTab();
    
    // strip full path off filename for display
    int idx = filename.lastIndexOf("/");
    filename.remove(0, idx+1);
    
    tabWidget->setTabText(tabWidget->currentIndex(), filename);
    /* new tab
     * set new tab name to filename
     * load in stuff
     * profit
     * */
>>>>>>> other
}

void MainWindow::closeTab()
{
    canvas.removeAt(tabWidget->currentIndex());
    tabWidget->removeTab(tabWidget->currentIndex());

}

void MainWindow::bold()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::justify()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
}

void MainWindow::center()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::setLineSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
                       tr("The <b>Menu</b> example shows how to create "
                          "menu-bar menus and context menus."));
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions()
{
    QFont boldFont;
    QFont italicFont;
    newAct = new QAction(tr("New Tab"), this);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("Close Tab"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(closeTab()));

    saveAct = new QAction(tr("Save File"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAct = new QAction(tr("Save File as..."), this);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    printAct = new QAction(tr("Open"), this);
    connect(printAct, SIGNAL(triggered()), this, SLOT(openFile()));

    exitAct = new QAction(tr("Activity"), this);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setStatusTip(tr("Delete the object"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteObject()));

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));

    italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, SIGNAL(triggered()),
            this, SLOT(setParagraphSpacing()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(deleteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);

}
