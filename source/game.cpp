#include "game.h"

Game::Game() :
    running(true),
    display(nullptr),
    queue(nullptr),
    timer(nullptr) {
    
}

void Game::init() {
    al_init();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    
    display = al_create_display(800, 600);
    timer = al_create_timer(1.0 / 60.0);
    queue = al_create_event_queue();
    
    al_register_event_source(queue, al_get_mouse_event_source());
    
    al_set_window_title(display, "Life of Judd");
}
