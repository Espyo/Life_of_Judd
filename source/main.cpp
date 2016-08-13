#include <iostream>

#include <allegro5/allegro.h>

#include "game.h"

using namespace std;


int main() {

    //TODO random blotches of ink and unclaimed turf
    
    Game game;
    game.init();
    game.loop();
    
    return 0;
    
}
