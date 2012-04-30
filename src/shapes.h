/* shapes.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef shapes_H
#define shapes_H

#include <QWidget>

class shapes
{
public:

    //Struct to contain basic properties all shapes share
    struct ObStruct
    {
        int iD;
        int posx;
        int posy;
        int linewidth;
        int size;
        QString shapetype;
        QColor color;
    };

    //Struct to contain line/arrow properties
    struct Arrows
    {
        int iD;
        int posx;
        int posy;
        int posxend;
        int posyend;
        int linewidth;
        QString shapetype;
        QColor color;
    };

    int count;
    shapes();
    void createEllipse();
    void createArrow();
    void createDashedArrow();
    void createLine();
    void createField();
    void createActor();
};

#endif // shapes_H
