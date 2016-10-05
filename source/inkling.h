#ifndef INCLUDED_INKLING_H
#define INCLUDED_INKLING_H

#include "point.h"


struct Chapter;


struct Inkling {
    Chapter* chapter;
    unsigned char team;
    Point pos;
    unsigned int ink_radius;
    float speed;
    float aggressiveness;
    float respawn_chance;
    
    Inkling(
        Chapter* chapter = nullptr,
        const Point start_pos = Point(),
        const unsigned char team = 0
    );
    void ink();
    void check_respawn();
    void move();
};


#endif //ifndef INCLUDED_INKLING_H
