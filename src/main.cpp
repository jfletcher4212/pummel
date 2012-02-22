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
    MainWindow window;
    window.show();
    return app.exec();
}
