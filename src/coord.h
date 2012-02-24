
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<math.h>
#include<assert.h>

using namespace std;

class coord
{
public:

    // overloaded the constructor
    coord();
    coord( double x, double y);
    coord( double min_x, double max_x, double min_y, double max_y);

    double get_x() { return _x;}
    double get_y() { return _y;}

    void print();
    double distance( coord * c);


private:

    double _x, _y;

};
