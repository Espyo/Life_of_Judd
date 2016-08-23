#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "chapter.h"
#include "game_state.h"


struct Game {
    bool running;
    float time_spent;
    
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT ev;
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* big_font;
    
    ALLEGRO_BITMAP* bmp_button_r_unselected;
    ALLEGRO_BITMAP* bmp_button_r_selected;
    ALLEGRO_BITMAP* bmp_button_l_unselected;
    ALLEGRO_BITMAP* bmp_button_l_selected;
    ALLEGRO_BITMAP* bmp_button_k_unselected;
    ALLEGRO_BITMAP* bmp_button_k_selected;
    ALLEGRO_BITMAP* bmp_picker_b;
    ALLEGRO_BITMAP* bmp_picker_i;
    ALLEGRO_BITMAP* bmp_picker_e;
    ALLEGRO_BITMAP* bmp_ink_effect;
    ALLEGRO_BITMAP* bmp_checkerboard;
    ALLEGRO_BITMAP* bmp_splash;
    ALLEGRO_BITMAP* bmp_logo;
    ALLEGRO_BITMAP* bmp_title_background;
    ALLEGRO_BITMAP* bmp_judd_r;
    ALLEGRO_BITMAP* bmp_judd_l;
    ALLEGRO_BITMAP* bmp_flag_r;
    ALLEGRO_BITMAP* bmp_flag_l;
    ALLEGRO_BITMAP* bmp_stamp_fail;
    ALLEGRO_BITMAP* bmp_stamp_pass;
    ALLEGRO_BITMAP* bmp_difficulty_icon[3];
    ALLEGRO_BITMAP* bmp_arena[N_ARENAS];
    ALLEGRO_BITMAP* bmp_arena_data[N_ARENAS];
    ALLEGRO_BITMAP* bmp_arena_bg[N_ARENAS];
    
    Game_State_Manager state_mgr;
    size_t chapter_to_load;
    unsigned char free_play_difficulty;
    Chapter cur_chapter;
    Chapter_Data random_chapter_data;
    vector<Chapter_Data> all_chapter_data;
    vector<pair<ALLEGRO_COLOR, ALLEGRO_COLOR> > all_ink_colors;
    
    Game();
    void loop();
    void draw_judd(
        const float pivot_x, const float pivot_y, const float scale,
        const bool right, const ALLEGRO_COLOR flag_color
    );
    
};


#endif //ifndef INCLUDED_GAME_H
