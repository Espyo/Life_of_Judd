#ifndef INCLUDED_MAIN_MENU_H
#define INCLUDED_MAIN_MENU_H

#include "game_state.h"


//Logo screen data.
const int LOGO_X = WINDOW_WIDTH * 0.5;
const int LOGO_Y = WINDOW_HEIGHT * 0.1;

//Judd screen data.
const int JUDD_PIVOT_X = WINDOW_WIDTH * 0.5;
const int JUDD_PIVOT_Y = WINDOW_HEIGHT - 8;
const float MAIN_MENU_JUDD_SCALE = 0.35;

//Story button screen data.
const int MAIN_MENU_STORY_X = WINDOW_WIDTH * 0.1;
const int MAIN_MENU_STORY_Y = WINDOW_HEIGHT * 0.25;
const int MAIN_MENU_STORY_W = 300;
const int MAIN_MENU_STORY_H = 32;

//Chapter info screen data.
const int CHAPTER_NAME_X = WINDOW_WIDTH * 0.2;
const int CHAPTER_NAME_Y = WINDOW_HEIGHT * 0.31;
const int CHAPTER_SCORE_X = WINDOW_WIDTH * 0.2;
const int CHAPTER_SCORE_Y = WINDOW_HEIGHT * 0.36;
const int CHAPTER_DIFFICULTY_X = WINDOW_WIDTH * 0.5;
const int CHAPTER_DIFFICULTY_ICON_X = WINDOW_WIDTH * 0.7;
const int CHAPTER_DIFFICULTY_NAME_X = WINDOW_WIDTH * 0.76;
const int CHAPTER_DIFFICULTY_Y = WINDOW_HEIGHT * 0.36;
const float DIFFICULTY_NAME_SCALE = 0.5;

//Chapter selector screen data.
const int PREV_BUTTON_X = WINDOW_WIDTH * 0.2;
const int PREV_BUTTON_W = 128;
const int PREV_BUTTON_H = 32;
const int NEXT_BUTTON_X = WINDOW_WIDTH * 0.4;
const int NEXT_BUTTON_W = 128;
const int NEXT_BUTTON_H = 32;
const int CHAPTER_BUTTON_Y = WINDOW_HEIGHT * 0.39;

//Free mode button screen data.
const int FREE_X = WINDOW_WIDTH * 0.1;
const int FREE_Y = WINDOW_HEIGHT * 0.51;
const int FREE_W = 380;
const int FREE_H = 32;

//Free mode difficulty selector screen data.
const int FREE_DIFFICULTY_X = WINDOW_WIDTH * 0.2;
const int FREE_DIFFICULTY_ICON_X = WINDOW_WIDTH * 0.4;
const int FREE_DIFFICULTY_NAME_X = WINDOW_WIDTH * 0.46;
const int FREE_DIFFICULTY_Y = WINDOW_HEIGHT * 0.57;
const int FREE_BUTTON_Y = WINDOW_HEIGHT * 0.61;

//Disclaimer screen data.
const int DISCLAIMER_X = WINDOW_WIDTH * 0.5;
const float DISCLAIMER_SCALE = 0.3;
const int DISCLAIMER_Y = WINDOW_HEIGHT - 32;
const string DISCLAIMER_TEXT =
    "This game is NOT affiliated with Nintendo® and should"
    " NOT be sold. Splatoon® is a trademark of Nintendo®.";

//Save warning screen data.
const int SAVE_WARNING_X = WINDOW_WIDTH * 0.5;
const int SAVE_WARNING_Y = 108;
const string SAVE_WARNING_TEXT =
    "UNABLE TO SAVE THE GAME! Please read the readme file.";
const float SAVE_WARNING_SCALE = 0.6f;


/* ----------------------------------------------------------------------------
 * Main menu game state.
 * Where the player chooses how to play the game.
 */
class Main_Menu : public Game_State {
private:

    //Is the mouse on top of a button?
    bool mouse_on_story_start_button;
    bool mouse_on_next_chapter_button;
    bool mouse_on_prev_chapter_button;
    bool mouse_on_free_play_start_button;
    bool mouse_on_next_difficulty_button;
    bool mouse_on_prev_difficulty_button;
    
    //Last chapter available to the player.
    size_t last_open_chapter;
    
    //Currently selected chapter.
    size_t chosen_chapter;
    
    //The logo is split into two colors. This is the divisor's X coordinate.
    float logo_split_x;
    
    //Colors for the logo.
    ALLEGRO_COLOR ink_colors[2];
    
    string get_difficulty_name(const int difficulty_number);
    
public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    explicit Main_Menu(Game* game);
    ~Main_Menu();
};


#endif //ifndef INCLUDED_MAIN_MENU_H
