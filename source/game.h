#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

struct Game {
    bool running;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT ev;
    
    void init();
    Game();
};

#endif //ifndef INCLUDED_GAME_H
