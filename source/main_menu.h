#ifndef INCLUDED_MAIN_MENU_H
#define INCLUDED_MAIN_MENU_H

#include "game_state.h"


class Main_Menu : public Game_State {
private:

    bool mouse_on_story_start_button;
    bool mouse_on_next_chapter_button;
    bool mouse_on_prev_chapter_button;
    bool mouse_on_free_play_start_button;
    bool mouse_on_next_difficulty_button;
    bool mouse_on_prev_difficulty_button;
    
    float logo_split_x;
    ALLEGRO_COLOR ink_colors[2];
    
    const int LOGO_X = WINDOW_WIDTH * 0.5;
    const int LOGO_Y = WINDOW_HEIGHT * 0.1;
    const int JUDD_PIVOT_X = WINDOW_WIDTH * 0.5;
    const int JUDD_PIVOT_Y = WINDOW_HEIGHT - 8;
    const float JUDD_SCALE = 0.25;
    const int STORY_X = WINDOW_WIDTH * 0.1;
    const int STORY_Y = WINDOW_HEIGHT * 0.25;
    const int STORY_W = 300;
    const int STORY_H = 32;
    const int CHAPTER_NAME_X = WINDOW_WIDTH * 0.2;
    const int CHAPTER_NAME_Y = WINDOW_HEIGHT * 0.31;
    const int CHAPTER_SCORE_X = WINDOW_WIDTH * 0.2;
    const int CHAPTER_SCORE_Y = WINDOW_HEIGHT * 0.35;
    const int CHAPTER_DIFFICULTY_X = WINDOW_WIDTH * 0.5;
    const int CHAPTER_DIFFICULTY_Y = WINDOW_HEIGHT * 0.35;
    const int PREV_BUTTON_X = WINDOW_WIDTH * 0.2;
    const int PREV_BUTTON_W = 128;
    const int PREV_BUTTON_H = 32;
    const int NEXT_BUTTON_X = WINDOW_WIDTH * 0.4;
    const int NEXT_BUTTON_W = 128;
    const int NEXT_BUTTON_H = 32;
    const int CHAPTER_BUTTON_Y = WINDOW_HEIGHT * 0.38;
    const int FREE_X = WINDOW_WIDTH * 0.1;
    const int FREE_Y = WINDOW_HEIGHT * 0.5;
    const int FREE_W = 380;
    const int FREE_H = 32;
    const int FREE_DIFFICULTY_X = WINDOW_WIDTH * 0.2;
    const int FREE_DIFFICULTY_Y = WINDOW_HEIGHT * 0.56;
    const int FREE_BUTTON_Y = WINDOW_HEIGHT * 0.59;
    const int DISCLAIMER_X = WINDOW_WIDTH * 0.5;
    const float DISCLAIMER_SCALE = 0.3;
    const int DISCLAIMER_1_Y = WINDOW_HEIGHT - 32;
    const string DISCLAIMER_1_TEXT =
        "This game is NOT affiliated with Nintendo® and should"
        " NOT be sold. Splatoon® is a trademark of Nintendo®.";
    const int DISCLAIMER_2_Y = WINDOW_HEIGHT - 16;
    const string DISCLAIMER_2_TEXT =
        "The copyrights of all associated characters, names, terms, art,"
        " music, and assets belong to Nintendo®.";
        
public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    Main_Menu(Game* game);
};


#endif //ifndef INCLUDED_MAIN_MENU_H
