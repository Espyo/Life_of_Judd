#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H


/* ----------------------------------------------------------------------------
 * A simple point class. Has data for X and Y coordinates, as floats.
 */
struct Point {
    float x;
    float y;
    Point(const float x = 0, const float y = 0);
    const Point operator +(const Point &p) const;
    const Point operator -(const Point &p) const;
    Point operator +=(const Point &p);
    const bool operator ==(const Point &p) const;
    const Point operator *(const float m) const;
};


#endif //ifndef INCLUDED_POINT_H
