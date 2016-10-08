#ifndef INCLUDED_INKLING_H
#define INCLUDED_INKLING_H

#include "point.h"


struct Chapter;


/* ----------------------------------------------------------------------------
 * An Inkling. A virtual player in a match. It moves around the arena,
 * inks as it goes, and sometimes respawns.
 */
struct Inkling {
    //Chapter it belongs to.
    Chapter* chapter;
    
    //Team ID.
    unsigned char team;
    
    //Current position on the grid.
    Point pos;
    
    //Each blotch of ink is a circle with this radius.
    unsigned int ink_radius;
    
    //Movement speed.
    float speed;
    
    //Aggressiveness towards aiming the opponents instead of exploring. 0 to 1.
    //0 = Always move in random directions.
    //1 = Always move towards the opponent's spawn point.
    float aggressiveness;
    
    //Chance of respawning on each iteration.
    //Also depends on proximity to the enemy's spawn point. 0 to 1.
    //0 =   Never respawns.
    //0.5 = 50% chance of respawning while on the enemy's spawn point.
    //1 =   Always respawning.
    float respawn_chance;
    
    Inkling(
        Chapter* chapter = nullptr,
        const Point &start_pos = Point(),
        const unsigned char team = 0
    );
    void ink();
    void check_respawn();
    void move();
};


#endif //ifndef INCLUDED_INKLING_H
