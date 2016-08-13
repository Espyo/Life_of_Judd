#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "arena.h"


struct Game {
    bool running;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT ev;
    
    Arena cur_arena;
    
    Game();
    void init();
    void loop();
};


#endif //ifndef INCLUDED_GAME_H
