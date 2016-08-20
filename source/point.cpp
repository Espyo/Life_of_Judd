#include "point.h"


Point::Point(const float x, const float y) :
    x(x),
    y(y) {
    
}


const Point Point::operator +(const Point &p) const {
    return Point(x + p.x, y + p.y);
}


const Point Point::operator -(const Point &p) const {
    return Point(x - p.x, y - p.y);
}


Point Point::operator +=(const Point &p) {
    x += p.x;
    y += p.y;
    return Point(x, y);
}


const bool Point::operator ==(const Point &p) const {
    return x == p.x && y == p.y;
}


const Point Point::operator *(const float m) const {
    return Point(x * m, y * m);
}
