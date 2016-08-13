#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include "arena.h"
#include "const.h"
#include "game_state.h"


class Gameplay : public Game_State {
private:
    Arena cur_arena;
    unsigned char game_mode;
    bool mouse_on_ok_button;
    unsigned char chosen_team;
    
    ALLEGRO_BITMAP* bmp_button_1;
    ALLEGRO_BITMAP* bmp_button_2;
    ALLEGRO_BITMAP* bmp_picker_1;
    ALLEGRO_BITMAP* bmp_picker_2;
    ALLEGRO_BITMAP* bmp_picker_3;
    ALLEGRO_BITMAP* bmp_ink_effect;
    
    const int OK_BUTTON_W = 128;
    const int OK_BUTTON_H = 128;
    const int OK_BUTTON_X = WINDOW_WIDTH - OK_BUTTON_W - 8;
    const int OK_BUTTON_Y = 8;
    
    const int PICKER_1_W = 750;
    const int PICKER_1_H = 94;
    const int PICKER_1_X = 25;
    const int PICKER_1_Y = WINDOW_HEIGHT - 8 - PICKER_1_H;
    
    const int PICKER_1_TEAM_BUTTON_W = 328;
    const int PICKER_1_TEAM_BUTTON_H = 70;
    const int PICKER_1_TEAM_BUTTON_Y = PICKER_1_Y + 13;
    const int PICKER_1_TEAM_1_BUTTON_X = PICKER_1_X + 32;
    const int PICKER_1_TEAM_2_BUTTON_X = PICKER_1_X + 390;
    
    void draw_ink_button(
        const int x, const int y, const int w, const int h,
        ALLEGRO_COLOR color, const bool moving
    );
    
public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    Gameplay(Game* game);
};


#endif //ifndef INCLUDED_GAMEPLAY_H
