#include <iostream>

#include <allegro5/allegro.h>

#include "game.h"

using namespace std;

int main() {

    Game game;
    game.init();
    
    while(game.running) {
        al_wait_for_event(game.queue, &game.ev);
        
    }
    
    return 0;
    
}
