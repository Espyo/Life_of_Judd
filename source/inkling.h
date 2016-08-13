#ifndef INCLUDED_INKLING_H
#define INCLUDED_INKLING_H

#include "point.h"


struct Arena;


struct Inkling {
    Arena* arena;
    Point pos;
    Point spawn;
    unsigned int ink_radius;
    unsigned char team;
    float speed;
    float aggressiveness;
    float respawn_chance;
    
    Inkling(
        Arena* arena = nullptr,
        const Point start_pos = Point(),
        const unsigned char team = 0
    );
    void ink();
    void check_respawn();
    void move();
};


#endif //ifndef INCLUDED_INKLING_H
