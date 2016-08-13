#ifndef INCLUDED_CONST_H
#define INCLUDED_CONST_H

#include <string>

#include <allegro5/allegro.h>

using namespace std;


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GAME_FPS = 30.0;
const string GAME_TITLE = "A Day in the Life of Judd";

const size_t N_TEAMS = 2;
const size_t N_INKLINGS = 4;
const float SPAWN_RADIUS = 4.0;

const ALLEGRO_COLOR COLOR_CLEAR = { 0.12, 0.12, 0.12, 1.0 };
const ALLEGRO_COLOR COLOR_VOID = { 0.0, 0.0, 0.0, 0.0 };


#endif //ifndef INCLUDED_CONST_H
