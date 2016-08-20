#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include "arena.h"
#include "const.h"
#include "game_state.h"


class Gameplay : public Game_State {
private:
    Arena cur_arena;
    unsigned char difficulty;
    unsigned char sub_state;
    float next_state_timer;
    
    unsigned char analysis_darken_opacity;
    
    bool mouse_on_ok_button;
    unsigned char chosen_team;
    int picker_team_x;
    bool mouse_down_on_team_picker;
    int picker_unclaimed_x;
    bool mouse_down_on_unclaimed_picker;
    
    float player_percentages[3];
    float player_score;
    
    enum SUB_STATES {
        SUB_STATE_PICKING,
        SUB_STATE_CELEBRATING,
        SUB_STATE_ANALYSIS_FADE_IN,
        SUB_STATE_ANALYSIS_1,
        SUB_STATE_ANALYSIS_2,
        SUB_STATE_ANALYSIS_FULL,
    };
    
    struct Confetto {
        Point pos;
        Point speed;
        ALLEGRO_COLOR color;
        float angle;
        float rotation_speed;
        
        static const int CONFETTO_SIZE = 16;
        
        bool tick();
        void draw();
    };
    
    vector<Confetto> confetti;
    
    const size_t N_CONFETTI = 150;
    const float CELEBRATION_DURATION = 2;
    const float ANALYSIS_DARKEN_VALUE = 160;
    const float ANALYSIS_FADE_DURATION = 0.5;
    const float ANALYSIS_DATA_DELAY = 0.8;
    
    const int PICKER_B_W = 750;
    const int PICKER_B_H = 94;
    const int PICKER_B_X = 25;
    const int PICKER_B_Y = WINDOW_HEIGHT - 4 - PICKER_B_H;
    
    const int PICKER_B_TEAM_BUTTON_W = 328;
    const int PICKER_B_TEAM_BUTTON_H = 70;
    const int PICKER_B_TEAM_BUTTON_Y = PICKER_B_Y + 13;
    const int PICKER_B_TEAM_1_BUTTON_X = PICKER_B_X + 32;
    const int PICKER_B_TEAM_2_BUTTON_X = PICKER_B_X + 390;
    
    const int PICKER_I_W = 750;
    const int PICKER_I_H = 94;
    const int PICKER_I_X = 25;
    const int PICKER_I_Y = WINDOW_HEIGHT - 4 - PICKER_I_H;
    
    const int PICKER_I_BAR_W = 684;
    const int PICKER_I_BAR_H = 68;
    const int PICKER_I_BAR_X = PICKER_I_X + 33;
    const int PICKER_I_BAR_Y = PICKER_I_Y + 13;
    
    const int PICKER_E_W = 750;
    const int PICKER_E_H = 151;
    const int PICKER_E_X = 25;
    const int PICKER_E_Y = WINDOW_HEIGHT - 4 - PICKER_E_H;
    
    const int PICKER_E_TEAM_BAR_W = 684;
    const int PICKER_E_TEAM_BAR_H = 68;
    const int PICKER_E_TEAM_BAR_X = PICKER_E_X + 33;
    const int PICKER_E_TEAM_BAR_Y = PICKER_E_Y + 13;
    
    const int PICKER_E_NONE_BAR_W = PICKER_E_TEAM_BAR_W;
    const int PICKER_E_NONE_BAR_H = 44;
    const int PICKER_E_NONE_BAR_X = PICKER_E_TEAM_BAR_X;
    const int PICKER_E_NONE_BAR_Y = PICKER_E_Y + 94;
    
    const int OK_BUTTON_W = 128;
    const int OK_BUTTON_H = 64;
    const int OK_BUTTON_X = WINDOW_WIDTH - OK_BUTTON_W - 25;
    const int OK_BUTTON_Y = PICKER_E_Y - OK_BUTTON_H - 4;
    
    const int ANALYSIS_HEADER_ROW_Y = WINDOW_HEIGHT * 0.1;
    const int ANALYSIS_HEADER_COLUMN_X = WINDOW_WIDTH * 0.3;
    const int ANALYSIS_LEFT_TEAM_X = WINDOW_WIDTH * 0.4;
    const int ANALYSIS_RIGHT_TEAM_X = WINDOW_WIDTH * 0.6;
    const int ANALYSIS_UNCLAIMED_X = WINDOW_WIDTH * 0.8;
    const int ANALYSIS_YOUR_DECISION_Y = WINDOW_HEIGHT * 0.2;
    const int ANALYSIS_REAL_Y = WINDOW_HEIGHT * 0.3;
    const int ANALYSIS_SCORE_X = WINDOW_WIDTH * 0.5;
    const int ANALYSIS_SCORE_Y = WINDOW_HEIGHT * 0.5;
    
    void draw_textured_rectangle(
        const int x, const int y, const int w, const int h,
        ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR color, const bool moving
    );
    void update_picker_x(
        int* var, const int mouse_value,
        const int bar_x, const int bar_w, const bool update_chosen_team,
        const bool mouse_value_is_delta
    );
    void calculate_player_percentages();
    void calculate_player_score();
    
public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    Gameplay(Game* game);
};


#endif //ifndef INCLUDED_GAMEPLAY_H
