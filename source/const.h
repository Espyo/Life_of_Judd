#ifndef INCLUDED_CONST_H
#define INCLUDED_CONST_H

#include <string>

#include <allegro5/allegro.h>

using namespace std;


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GAME_FPS = 30.0;
const string GAME_TITLE = "A Day in the Life of Judd";

const string GRAPHICS_FOLDER = "graphics";
const string BMP_BUTTON_1 = "button_1.png";
const string BMP_BUTTON_2 = "button_2.png";
const string BMP_PICKER_1 = "picker_1.png";
const string BMP_PICKER_2 = "picker_2.png";
const string BMP_PICKER_3 = "picker_3.png";
const string BMP_INK_EFFECT = "ink_effect.png";

enum GAME_STATES {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_GAMEPLAY,
};

enum GAME_MODES {
    GAME_MODE_BEGINNER,
    GAME_MODE_INTERMEDIATE,
    GAME_MODE_EXPERT,
};

const size_t N_TEAMS = 2;
const size_t N_INKLINGS = 4;
const float SPAWN_RADIUS = 4.0;

const ALLEGRO_COLOR COLOR_CLEAR = { 0.12, 0.12, 0.12, 1.0 };
const ALLEGRO_COLOR COLOR_VOID = { 0.0, 0.0, 0.0, 0.0 };


#endif //ifndef INCLUDED_CONST_H
