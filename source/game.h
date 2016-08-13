#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "bitmap_manager.h"
#include "game_state.h"


struct Game {
    bool running;
    float time_spent;
    
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT ev;
    ALLEGRO_FONT* font;
    
    Game_State_Manager state_mgr;
    Bitmap_Manager bmp_mgr;
    
    Game();
    void loop();
};


#endif //ifndef INCLUDED_GAME_H
