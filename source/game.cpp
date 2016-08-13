#include "const.h"
#include "game.h"
#include "utils.h"


Game::Game() :
    running(true),
    display(nullptr),
    queue(nullptr),
    timer(nullptr) {
    
}


void Game::init() {
    srand(time(NULL));
    
    al_init();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    timer = al_create_timer(1.0 / GAME_FPS);
    queue = al_create_event_queue();
    
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    
    al_set_window_title(display, GAME_TITLE.c_str());
}


void Game::loop() {
    cur_arena.load();
    cur_arena.do_match();
    cur_arena.calculate_real_percentages();
    cur_arena.render();
    
    al_start_timer(timer);
    
    ALLEGRO_FONT* font = al_create_builtin_font(); //TODO;
    
    while(running) {
        al_wait_for_event(queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            al_set_target_backbuffer(display);
            al_clear_to_color(al_map_rgb(16, 32, 16));
            
            al_draw_bitmap(cur_arena.background_bmp, 0, 0, 0);
            al_draw_bitmap(cur_arena.result_bmp, 0, 0, 0);
            
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, f2s(cur_arena.real_percentages[0]).c_str());
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 8, 0, f2s(cur_arena.real_percentages[1]).c_str());
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 16, 0, f2s(cur_arena.real_percentages[2]).c_str());
            
            al_flip_display();
            
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            
        }
    }
    
    al_save_bitmap("bmp.png", cur_arena.background_bmp);
}
