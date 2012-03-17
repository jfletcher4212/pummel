/* shapes.cpp -contains the functions to store default properties in the shape structs
               and contains the creation function for each shape
               Made by Theora Rice
  */
#include "shapes.h"
#include <QtGui>


shapes::shapes()
{
}
//Creating a default ellipse
void shapes::createEllipse()
{
    ObStruct shapename;
    shapename.iD = count++;
    shapename.size = 5;
    shapename.posx = 0;
    shapename.posy = 0;
    shapename.linewidth = 1;
    shapename.shapetype = "shapename";
    shapename.color = "black";

    QPainter circle;
    circle.setPen( "black" );
    QRectF rectangle(20, 20, 100, 50);
    circle.drawEllipse(rectangle);
}

//creating default arrow
void shapes::createArrow()
{
    Arrows shapename;
    shapename.iD = count++;
    shapename.posx = 0;
    shapename.posy = 0;
    shapename.posxend = 5;
    shapename.posyend = 5;
    shapename.linewidth = 1;
    shapename.shapetype = "shapename";
    shapename.color = "black";
}

//creating default dashed arrow
void shapes::createDashedArrow()
{
    Arrows shapename;
    shapename.iD = count++;
    shapename.posx = 0;
    shapename.posy = 0;
    shapename.posxend = 5;
    shapename.posyend = 5;
    shapename.linewidth = 1;
    shapename.shapetype = "dashed-arrow";
    shapename.color = "black";
}

//creating default line
void shapes::createLine()
{
    QLineF line(105, 70, 140, 100);
    QPainter painter;
    Arrows shapename;
    shapename.iD = count++;
    shapename.posx = 0;
    shapename.posy = 0;
    shapename.posxend = 5;
    shapename.posyend = 5;
    shapename.linewidth = 1;
    shapename.shapetype = "line";
    shapename.color = "black";

    painter.drawLine(line);
}

//creating default field (box)
void shapes::createField()
{
    ObStruct field;
    field.iD = count++;
    field.size = 5;
    field.posx = 0;
    field.posy = 0;
    field.linewidth = 1;
    field.shapetype = "field";
    field.color = "black";
}

//creating default actor
void shapes::createActor()
{
    ObStruct actor;
    actor.iD = count++;
    actor.size = 5;
    actor.posx = 0;
    actor.posy = 0;
    actor.linewidth = 1;
    actor.shapetype = "actor";
    actor.color = "black";
}
