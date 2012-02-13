/* main.cpp - file that displays windows.
  */
#include <QtGui/QApplication>
#include "shapes.h"
#include "drawarea.h"
#include "mainwindow.h"
#include "toolbar.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //main drawing area
   // DrawArea w;
    //background file layout
    MainWindow window;
    //toolbar
    //Toolbar x;

    //x.show();
    window.show();
   // w.show();

    return app.exec();
}
