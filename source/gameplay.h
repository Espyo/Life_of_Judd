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
    int picker_team_x;
    bool mouse_down_on_team_picker;
    int picker_unclaimed_x;
    bool mouse_down_on_unclaimed_picker;
    
    ALLEGRO_BITMAP* bmp_button_1;
    ALLEGRO_BITMAP* bmp_button_2;
    ALLEGRO_BITMAP* bmp_picker_1;
    ALLEGRO_BITMAP* bmp_picker_2;
    ALLEGRO_BITMAP* bmp_picker_3;
    ALLEGRO_BITMAP* bmp_ink_effect;
    ALLEGRO_BITMAP* bmp_checkerboard;
    
    const int OK_BUTTON_W = 128;
    const int OK_BUTTON_H = 128;
    const int OK_BUTTON_X = WINDOW_WIDTH - OK_BUTTON_W - 8;
    const int OK_BUTTON_Y = 8;
    
    const int PICKER_B_W = 750;
    const int PICKER_B_H = 94;
    const int PICKER_B_X = 25;
    const int PICKER_B_Y = WINDOW_HEIGHT - 8 - PICKER_B_H;
    
    const int PICKER_B_TEAM_BUTTON_W = 328;
    const int PICKER_B_TEAM_BUTTON_H = 70;
    const int PICKER_B_TEAM_BUTTON_Y = PICKER_B_Y + 13;
    const int PICKER_B_TEAM_1_BUTTON_X = PICKER_B_X + 32;
    const int PICKER_B_TEAM_2_BUTTON_X = PICKER_B_X + 390;
    
    const int PICKER_I_W = 750;
    const int PICKER_I_H = 94;
    const int PICKER_I_X = 25;
    const int PICKER_I_Y = WINDOW_HEIGHT - 8 - PICKER_I_H;
    
    const int PICKER_I_BAR_W = 684;
    const int PICKER_I_BAR_H = 68;
    const int PICKER_I_BAR_X = PICKER_I_X + 33;
    const int PICKER_I_BAR_Y = PICKER_I_Y + 13;
    
    const int PICKER_E_W = 750;
    const int PICKER_E_H = 151;
    const int PICKER_E_X = 25;
    const int PICKER_E_Y = WINDOW_HEIGHT - 8 - PICKER_E_H;
    
    const int PICKER_E_TEAM_BAR_W = 684;
    const int PICKER_E_TEAM_BAR_H = 68;
    const int PICKER_E_TEAM_BAR_X = PICKER_E_X + 33;
    const int PICKER_E_TEAM_BAR_Y = PICKER_E_Y + 13;
    
    const int PICKER_E_NONE_BAR_W = PICKER_E_TEAM_BAR_W;
    const int PICKER_E_NONE_BAR_H = 44;
    const int PICKER_E_NONE_BAR_X = PICKER_E_TEAM_BAR_X;
    const int PICKER_E_NONE_BAR_Y = PICKER_E_Y + 94;
    
    void draw_textured_rectangle(
        const int x, const int y, const int w, const int h,
        ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR color, const bool moving
    );
    void update_picker_x(
        int* var, const int mouse_x,
        const int bar_x, const int bar_w, const bool update_chosen_team
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
