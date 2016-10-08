#include "point.h"


/* ----------------------------------------------------------------------------
 * Constructs a point, given its coordinates.
 */
Point::Point(const float x, const float y) :
    x(x),
    y(y) {
    
}


/* ----------------------------------------------------------------------------
 * Adds the coordinates of two points.
 */
const Point Point::operator +(const Point &p) const {
    return Point(x + p.x, y + p.y);
}


/* ----------------------------------------------------------------------------
 * Subtracts the coordinates of two points.
 */
const Point Point::operator -(const Point &p) const {
    return Point(x - p.x, y - p.y);
}


/* ----------------------------------------------------------------------------
 * Adds the coordinates of another point to this one's.
 */
Point Point::operator +=(const Point &p) {
    x += p.x;
    y += p.y;
    return Point(x, y);
}


/* ----------------------------------------------------------------------------
 * Compares if two points are the same.
 */
const bool Point::operator ==(const Point &p) const {
    return x == p.x && y == p.y;
}


/* ----------------------------------------------------------------------------
 * Multiplies the coordinates by a number.
 */
const Point Point::operator *(const float m) const {
    return Point(x * m, y * m);
}
