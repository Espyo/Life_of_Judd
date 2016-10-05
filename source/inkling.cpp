#include <algorithm>

#include "chapter.h"
#include "inkling.h"
#include "utils.h"


Inkling::Inkling(
    Chapter* chapter,
    const Point start_pos,
    const unsigned char team
) :
    chapter(chapter),
    team(team),
    pos(start_pos),
    ink_radius(0),
    speed(0),
    aggressiveness(0),
    respawn_chance(0) {
    
    
}


void Inkling::ink() {
    chapter->ink(pos, ink_radius, team);
}


void Inkling::check_respawn() {
    Point dif =
        team == 0 ?
        chapter->spawns[1] - pos :
        chapter->spawns[0] - pos;
        
    float other_spawn_closeness =
        min(1.0f, sqrt(dif.x * dif.x + dif.y * dif.y) / (chapter->spawn_dist));
    other_spawn_closeness = 1 - other_spawn_closeness;
    
    if(randomf(0, 1) <= other_spawn_closeness * respawn_chance) {
        pos = chapter->spawns[team];
    }
}


void Inkling::move() {
    Point new_pos = pos;
    
    Point other_spawn =
        team == 0 ?
        chapter->spawns[1] :
        chapter->spawns[0];
        
    float intended_angle =
        atan2(
            other_spawn.y - new_pos.y,
            other_spawn.x - new_pos.x
        );
    intended_angle +=
        randomf((-M_PI) * (1 - aggressiveness), M_PI * (1 - aggressiveness));
        
    new_pos.x += cos(intended_angle) * speed;
    new_pos.y += sin(intended_angle) * speed;
    
    if(chapter->is_valid(new_pos, false)) {
        pos = new_pos;
    }
}
