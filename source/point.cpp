#include "point.h"


Point::Point(const float x, const float y) :
    x(x),
    y(y) {
    
}


const Point Point::operator+(const Point &p) const {
    return Point(x + p.x, y + p.y);
}
