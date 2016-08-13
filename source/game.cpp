#include "const.h"
#include "game.h"
#include "gameplay.h"
#include "utils.h"


Game::Game() :
    running(true),
    display(nullptr),
    queue(nullptr),
    timer(nullptr),
    state_mgr() {
    
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
    font = al_create_builtin_font(); //TODO;
    
    bmp_mgr.load_bitmap(BMP_BUTTON_1);
    bmp_mgr.load_bitmap(BMP_BUTTON_2);
    bmp_mgr.load_bitmap(BMP_PICKER_1);
    bmp_mgr.load_bitmap(BMP_PICKER_2);
    bmp_mgr.load_bitmap(BMP_PICKER_3);
    bmp_mgr.load_bitmap(BMP_INK_EFFECT);
    
    state_mgr.register_state(GAME_STATE_GAMEPLAY, new Gameplay(this));
    state_mgr.change_state(GAME_STATE_GAMEPLAY);
    
    al_start_timer(timer);
}


void Game::loop() {
    al_start_timer(timer);
    
    while(running) {
        al_wait_for_event(queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            time_spent += 1.0 / GAME_FPS;
            state_mgr.get_current_state()->do_drawing();
            state_mgr.get_current_state()->do_logic();
            
            
        } else if(
            ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
            ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
            ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP
        ) {
            state_mgr.get_current_state()->handle_mouse(ev);
            
            
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            
        }
    }
}
