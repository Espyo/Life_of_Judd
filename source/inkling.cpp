#include <algorithm>

#include "arena.h"
#include "inkling.h"
#include "utils.h"


Inkling::Inkling(
    Arena* arena,
    const Point start_pos,
    const unsigned char team
) :
    arena(arena),
    ink_radius(0),
    team(team),
    speed(0),
    aggressiveness(0),
    respawn_chance(0) {
    
    spawn = start_pos;
    pos = start_pos;
}


void Inkling::ink() {
    arena->ink(pos, ink_radius, team);
}


void Inkling::check_respawn() {
    float dx = arena->width / 2.0 - pos.x;
    float dy = arena->height / 2.0 - pos.y;
    float center_closeness =
        min(1.0, sqrt(dx * dx + dy * dy) / (arena->width / 2.0)); //TODO don't use arena width; use distance to spawn or something
    center_closeness = 1 - center_closeness;
    
    if(randomf(0, 1) <= center_closeness * respawn_chance) {
        pos = spawn;
    }
}


void Inkling::move() {
    Point new_pos = pos;
    
    Point other_spawn = team == 0 ? arena->spawns[1] : arena->spawns[0];
    
    float intended_angle =
        atan2(
            other_spawn.y - new_pos.y,
            other_spawn.x - new_pos.x
        );
    intended_angle +=
        randomf((-M_PI) * (1 - aggressiveness), M_PI * (1 - aggressiveness));
        
    new_pos.x += cos(intended_angle) * speed;
    new_pos.y += sin(intended_angle) * speed;
    
    if(arena->is_valid(new_pos)) {
        pos = new_pos;
    }
}
