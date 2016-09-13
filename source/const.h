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
const string FONT_FILE_NAME = "Waree-Bold.ttf";
const int FONT_SIZE = 40;
const ALLEGRO_COLOR COLOR_CLEAR = { 0.12, 0.12, 0.12, 1.0 };
const ALLEGRO_COLOR COLOR_VOID = { 0.0, 0.0, 0.0, 0.0 };

const string BMP_BUTTON_R_UNSELECTED = "button_r_unselected.png";
const string BMP_BUTTON_R_SELECTED =   "button_r_selected.png";
const string BMP_BUTTON_L_UNSELECTED = "button_l_unselected.png";
const string BMP_BUTTON_L_SELECTED =   "button_l_selected.png";
const string BMP_BUTTON_K_UNSELECTED = "button_k_unselected.png";
const string BMP_BUTTON_K_SELECTED =   "button_k_selected.png";
const string BMP_BUTTON_S_UNSELECTED = "button_s_unselected.png";
const string BMP_BUTTON_S_SELECTED =   "button_s_selected.png";
const string BMP_PICKER_B = "picker_b.png";
const string BMP_PICKER_I = "picker_i.png";
const string BMP_PICKER_E = "picker_e.png";
const string BMP_INK_EFFECT = "ink_effect.png";
const string BMP_CHECKERBOARD = "checkerboard.png";
const string BMP_SPLASH = "splash.png";
const string BMP_LOGO = "logo.png";
const string BMP_TITLE_BG = "title_background.png";
const string BMP_JUDD_R = "judd_r.png";
const string BMP_JUDD_L = "judd_l.png";
const string BMP_FLAG_R = "flag_r.png";
const string BMP_FLAG_L = "flag_l.png";
const string BMP_STAMP_FAIL = "stamp_fail.png";
const string BMP_STAMP_PASS = "stamp_pass.png";
const string BMP_BEGINNER_ICON = "beginner_icon.png";
const string BMP_INTERMEDIATE_ICON = "intermediate_icon.png";
const string BMP_EXPERT_ICON = "expert_icon.png";

enum GAME_STATES {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_LOADING,
    GAME_STATE_GAMEPLAY,
};

enum DIFFICULTIES {
    DIFFICULTY_BEGINNER,
    DIFFICULTY_INTERMEDIATE,
    DIFFICULTY_EXPERT,
};

enum TEAMS {
    TEAM_1,
    TEAM_2,
    TEAM_NONE,
};

const size_t N_INKLINGS = 4;
const size_t N_ARENAS = 5; //TODO;
const float SPAWN_RADIUS = 9.0;
const float PASSING_SCORE = 95;


#endif //ifndef INCLUDED_CONST_H
