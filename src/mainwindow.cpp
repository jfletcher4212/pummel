
#include <QtGui>

#include "mainwindow.h"
#include "borderlayout.h"
#include "global.h"
#include "xml_io.h"
#include "saveprompt.h"
#include "hintbox.h"
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

MainWindow::~MainWindow()
{
    delete widget;
    delete layout;

    delete fileMenu;
    delete editMenu;
    delete formatMenu;
    delete helpMenu;
    delete objectsMenu;
    delete alignmentGroup;
    delete newAct;
    delete closeAct;
    delete saveAct;
    delete saveAsAct;
    delete openAct;
    delete exitAct;
    delete undoAct;
    delete redoAct;
    delete cutAct;
    delete copyAct;
    delete pasteAct;
    delete deleteObjAct;
    delete deleteSelectedAct;
    delete boldAct;
    delete italicAct;
    delete leftAlignAct;
    delete rightAlignAct;
    delete justifyAct;
    delete centerAct;
    delete setLineSpacingAct;
    delete setParagraphSpacingAct;
    delete aboutAct;
    delete aboutQtAct;
    delete hintAct;

    delete infoLabel;

    delete hintDialog;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(false);
    contextEventPos = canvas.at(tabWidget->currentIndex())->view->mapToScene(event->pos());

    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.addAction(deleteObjAct);
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
    //canvas.at(tabWidget->currentIndex())->testAction();

}

void MainWindow::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::deleteObj()
{
    /*
    if(canvas.at(tabWidget->currentIndex())->scene->sceneItemAt(contextEventPos))
    {
        int index = canvas.at(tabWidget->currentIndex())->scene->sceneItemAt(contextEventPos);
      //  canvas.at(tabWidget->currentIndex())->scene->deleteItem();
        //canvas.at(tabWidget->currentIndex())->scene->getObjectList().at()
        printf("%d\n", index);
    }
    */
}

void MainWindow::deleteSelected()
{
    int iconSelectedIndex = -1;
    for(int i = 0; i < canvas.at(tabWidget->currentIndex())->scene->getObjectList().size(); i++)
    {
        if(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(i)->isSelected())
        {
            iconSelectedIndex = i;
        }
    }

    if(iconSelectedIndex < 0)
    {
        return;
    }
    else
    {
	// this needs to also do an index shift or file loading will break
        canvas.at(tabWidget->currentIndex())->scene->deleteItem(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(iconSelectedIndex));
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
/*Creates a new tab with a default 'untitled' filename*/
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
/* Creates a new tab with the specified filename*/
void MainWindow::newTab(QString filename, QList<Icon*> item_list,  QList<lineBody*> line_list, QString d_type)
{
    int i = tabWidget->count();
    next_tab_num++;
    
    //qDebug() << "making new drawarea";
    DrawArea *newCanvas = new DrawArea(0, 250, 250, item_list,  line_list, d_type);
    
    //newCanvas->render_icons(tmplist);
    //newCanvas->render_lines(tmplist[1]);
    
    canvas.append(newCanvas);
    tabWidget->insertTab(i, newCanvas, filename);
    tabWidget->setCurrentIndex(i);
    tabWidget->widget(i)->setVisible(true);
}
/*
 * If a filename has been specified, saveFile will
 * automatically save to that filename. Otherwise,
 * it will call SaveAsFile to get a filename
 */
void MainWindow::saveFile()
{
    QString filename = tabWidget->tabText(tabWidget->currentIndex());
    if(filename == "untitled")
    {
        saveAsFile();
    }
    else
    {
	DrawArea *tmpscene = canvas.at(tabWidget->currentIndex());
	Xml_io writer(tmpscene->getObjects(), tmpscene->getLines(), filename, (DiagramType)tmpscene->getDiagramType());
	
	// write the file
	writer.write_xml();
    }
}
void MainWindow::saveAsFile()
{
    // dialog box for user to enter filename
    QString filename = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "*.xml");
    if(filename == "")
    {
        cout << "No filename given" << endl;
    }
    else
    {
	DrawArea *tmpscene = canvas.at(tabWidget->currentIndex());
        Xml_io writer(tmpscene->getObjects(), tmpscene->getLines(), filename, (DiagramType)tmpscene->getDiagramType());
	
        // write the file
        writer.write_xml();
	
	// make the tab
	tabWidget->setTabText(tabWidget->currentIndex(), filename );
    }
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
    
    if( filename != "" )
    {
        Xml_io writer(filename);
	
	// parse the xml
	writer.parse_xml();
	QList<Icon*> icon_list = writer.get_items();
	QList<lineBody*> line_list = writer.get_lines();
	
        // make the tab
        newTab(filename, icon_list, line_list, writer.get_diagram_type());
        tabWidget->setTabText(tabWidget->currentIndex(), filename);
    }
}

/*
 *    open a savePrompt window
 *      with the following options:
 *  save&quit:
 *    run saveFile subroutine (see above)
 *    proceed
 *  save w/out quitting
 *    proceed
 *  cancel
 *    do nothing
 *
 * Note: currently, this only runs when the 'close tab' button
 * is selected from the File menu.
 */
void MainWindow::closeTab()
{

    g_savepromptval;
    savePrompt *question = new savePrompt;
    question->exec();
    if(g_savepromptval == 1)
    {
        saveFile();
        if( canvas.length() == 1 )
        {
            this->close();
        }
        else
        {
            canvas.removeAt(tabWidget->currentIndex());
            tabWidget->removeTab(tabWidget->currentIndex());
        }
    }
    if(g_savepromptval == -1)
    {
        if( canvas.length() == 1 )
        {
            this->close();
        }
        else
        {
            canvas.removeAt(tabWidget->currentIndex());
            tabWidget->removeTab(tabWidget->currentIndex());
        }
    }

}

void MainWindow::bold(){}

void MainWindow::italic(){}

void MainWindow::leftAlign(){}

void MainWindow::rightAlign(){}

void MainWindow::justify(){}

void MainWindow::center(){}

void MainWindow::setLineSpacing(){}

void MainWindow::setParagraphSpacing(){}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About PUML/Pummel"),
                       tr("PUML is a UML diagram editor"
                          "created by Team Pummel"
                          "for CS384."));
}

void MainWindow::hints()
{
    hintDialog->show();
}

void MainWindow::aboutQt(){}
void MainWindow::exit()
{
    hintDialog->close();
    close();
}

void MainWindow::createActions()
{
    QFont boldFont;
    QFont italicFont;
    newAct = new QAction(tr("New Tab"), this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    closeAct = new QAction(tr("Close Tab"), this);
    closeAct->setShortcut(QKeySequence::Cut);
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closeTab()));

    saveAct = new QAction(tr("Save Diagram"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save with the current diagram"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAct = new QAction(tr("Save Diagram as..."), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the current diagram with a specified filename"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    openAct = new QAction(tr("Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    exitAct->setStatusTip(tr("Closes the entire program"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    hintDialog = new HintBox;
    hintAct = new QAction(tr("Hints and Tips"), this);
    hintAct->setStatusTip(tr("Show a small tips dialog"));
    connect(hintAct, SIGNAL(triggered()), this, SLOT(hints()));


    //marked for deletion
    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
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


    deleteObjAct = new QAction(tr("&Delete Object"), this);
    deleteObjAct->setStatusTip(tr("Delete the object"));
    connect(deleteObjAct, SIGNAL(triggered()), this, SLOT(deleteObj()));


    deleteSelectedAct = new QAction(tr("&Delete Selected"), this);
    deleteSelectedAct->setStatusTip(tr("Delete the selected object(s)"));
    deleteSelectedAct->setShortcuts(QKeySequence::Delete);
    connect(deleteSelectedAct, SIGNAL(triggered()), this, SLOT(deleteSelected()));

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
//all this ^^^ marked for deletion
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(closeAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(exitAct);
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(hintAct);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

/*    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);*/

}
