/* params.h - provides the paramaters for object.
   Made by Coleman Beaseley - 12/16/2011
  */
#ifndef PARAMS_H
#define PARAMS_H

using namespace std;

//parameters for shapes
struct shapeParams
{
    string name;
    QString fillColor;
    int weight;
};

//parameters for lines
struct lineParams
{
    QString color;
    int weight;
};

//parameters for text
struct textParams
{
    QString font;
    QString color;
    int size;
};


#endif // PARAMS_H
