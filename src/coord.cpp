
#include "coord.h"

coord::coord()
{
    _x = _y = 0;
    // this->_x = this->_y = 0;
}

coord::coord( double x, double y)
{
    _x = x;
    _y = y;
}

coord::coord( double min_x, double max_x, double min_y, double max_y)
{
    _x = (double) rand() / (double) RAND_MAX * (max_x - min_x) + min_x;
    _y = (double) rand() / (double) RAND_MAX * (max_y - min_y) + min_y;
}

void coord::print()
{
    /*
    cout<<_x;
    cout<<",";
    cout<<_y;
    */

    cout<<_x<<","<<_y;
}

double coord::distance( coord * c)
{
    double dx = _x - c->_x;
    double dy = _y - c->_y;

    return sqrt( dx*dx + dy*dy );
}
