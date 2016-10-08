#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "chapter.h"
#include "const.h"
#include "game_state.h"


//Interval between characters of a story script block.
const float MESSAGE_CHAR_INTERVAL = 0.03;

//Total number of confetti.
const size_t N_CONFETTI = 150;

//Total duration of Judd's pop-up hop.
const float JUDD_HOP_DURATION = 1;

//How long to do the team picking celebration for.
const float CELEBRATION_DURATION = 2;

//The analysis screen darkens what's behind by this much (0 to 255).
const float ANALYSIS_DARKEN_VALUE = 160;

//The analysis screen fades in for this long.
const float ANALYSIS_FADE_DURATION = 0.5;

//Points of data on the analysis screen appear this far apart.
const float ANALYSIS_DATA_DELAY = 0.8;

//Story script screen data.
const int STORY_SCRIPT_X = 8;
const int STORY_SCRIPT_Y = WINDOW_HEIGHT * 0.2;
const float STORY_SCALE = 0.75;

//Story skip button screen data.
const int SKIP_BUTTON_W = 128;
const int SKIP_BUTTON_H = 64;
const int SKIP_BUTTON_X = WINDOW_WIDTH - SKIP_BUTTON_W - 8;
const int SKIP_BUTTON_Y = 8;

//Story "click to continue" screen data.
const int STORY_CLICK_NOTE_X = WINDOW_WIDTH * 0.95;
const int STORY_CLICK_NOTE_Y = WINDOW_HEIGHT * 0.95;
const float STORY_CLICK_NOTE_SCALE = 0.4;

//Begginner picker screen data.
const int PICKER_B_W = 750;
const int PICKER_B_H = 94;
const int PICKER_B_X = 25;
const int PICKER_B_Y = WINDOW_HEIGHT - 4 - PICKER_B_H;

const int PICKER_B_TEAM_BUTTON_W = 328;
const int PICKER_B_TEAM_BUTTON_H = 70;
const int PICKER_B_TEAM_BUTTON_Y = PICKER_B_Y + 13;
const int PICKER_B_TEAM_1_BUTTON_X = PICKER_B_X + 32;
const int PICKER_B_TEAM_2_BUTTON_X = PICKER_B_X + 390;

//Intermediate picker screen data.
const int PICKER_I_W = 750;
const int PICKER_I_H = 126;
const int PICKER_I_X = 25;
const int PICKER_I_Y = WINDOW_HEIGHT - 4 - PICKER_I_H;

const int PICKER_I_BAR_W = 684;
const int PICKER_I_BAR_H = 68;
const int PICKER_I_BAR_X = PICKER_I_X + 33;
const int PICKER_I_BAR_Y = PICKER_I_Y + 45;
const int PICKER_I_UNINKED_X = PICKER_I_X + 250;
const int PICKER_I_UNINKED_Y = PICKER_I_Y + 13;
const int PICKER_I_UNINKED_W = 250;
const int PICKER_I_UNINKED_H = 19;
const float PICKER_I_UNINKED_SCALE = 0.5;

//Expert picker screen data.
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

//Back button screen data.
const int BACK_BUTTON_W = 128;
const int BACK_BUTTON_H = 64;
const int BACK_BUTTON_X = 8;
const int BACK_BUTTON_Y = PICKER_E_Y - BACK_BUTTON_H - 4;

//OK button screen data.
const int OK_BUTTON_W = 128;
const int OK_BUTTON_H = 64;
const int OK_BUTTON_X = WINDOW_WIDTH - OK_BUTTON_W - 8;
const int OK_BUTTON_Y = PICKER_E_Y - OK_BUTTON_H - 4;

//Judd's starting poisition, before the hop.
const int JUDD_START_Y = WINDOW_WIDTH + 100;

//Judd's drawing scale.
const float JUDD_SCALE = 0.3;

//Analysis screen data.
const int ANALYSIS_HEADER_COLUMN_X = WINDOW_WIDTH * 0.3;
const int ANALYSIS_LEFT_TEAM_X = WINDOW_WIDTH * 0.4;
const int ANALYSIS_RIGHT_TEAM_X = WINDOW_WIDTH * 0.6;
const int ANALYSIS_UNCLAIMED_X = WINDOW_WIDTH * 0.8;
const int ANALYSIS_YOUR_DECISION_Y = WINDOW_HEIGHT * 0.2;
const int ANALYSIS_REAL_Y = WINDOW_HEIGHT * 0.3;
const int ANALYSIS_HEADER_ROW_Y = WINDOW_HEIGHT * 0.1;
const int ANALYSIS_SCORE_X = WINDOW_WIDTH * 0.35;
const int ANALYSIS_SCORE_Y = WINDOW_HEIGHT * 0.5;
const int ANALYSIS_COMMENT_X = WINDOW_WIDTH * 0.5;
const int ANALYSIS_COMMENT_Y = WINDOW_HEIGHT * 0.7;
const float ANALYSIS_COMMENT_SCALE = 0.5;
const int ANALYSIS_COMMENT_SIGNED_X = WINDOW_WIDTH * 0.7;
const int ANALYSIS_COMMENT_SIGNED_Y = WINDOW_HEIGHT * 0.8;
const float ANALYSIS_COMMENT_SIGNED_SCALE = 0.5;
const int ANALYSIS_STAMP_X = WINDOW_WIDTH * 0.75;
const int ANALYSIS_STAMP_Y = WINDOW_HEIGHT * 0.5;
const float ANALYSIS_STAMP_ANGLE = -(M_PI * 0.15);
const float ANALYSIS_STAMP_SCALE = 0.6;
const int ANALYSIS_CLICK_NOTE_X = WINDOW_WIDTH * 0.95;
const int ANALYSIS_CLICK_NOTE_Y = WINDOW_HEIGHT * 0.95;
const float ANALYSIS_CLICK_NOTE_SCALE = 0.4;


/* ----------------------------------------------------------------------------
 * Gameplay game state.
 * This is the core gameplay, where the player does stuff.
 */
class Gameplay : public Game_State {
private:

    enum SUB_STATES {
        //Writing characters of the current story block.
        SUB_STATE_STORY_WRITING,
        //Waiting for the player to advance the story block.
        SUB_STATE_STORY_WAITING,
        //Player is picking the results.
        SUB_STATE_PICKING,
        //Celebrating the player's pick.
        SUB_STATE_CELEBRATING,
        //Analysis screen is fading in.
        SUB_STATE_ANALYSIS_FADE_IN,
        //Showing first part of the analysis.
        SUB_STATE_ANALYSIS_1,
        //Showing second part of the analysis.
        SUB_STATE_ANALYSIS_2,
        //Showing the full analysis screen.
        SUB_STATE_ANALYSIS_FULL,
    };
    
    //A piece of confetto. It's basically a particle.
    struct Confetto {
        //Current position.
        Point pos;
        //Current movement speed, in pixels per second.
        Point speed;
        //Color.
        ALLEGRO_COLOR color;
        //Current angle.
        float angle;
        //Rotation speed, in radians per second.
        float rotation_speed;
        
        //Each confetto has these dimensions.
        static const int CONFETTO_W = 16;
        static const int CONFETTO_H = 8;
        
        bool tick();
        void draw();
    };
    
    //Current difficulty.
    unsigned char difficulty;
    
    //Logic sub-state.
    unsigned char sub_state;
    
    //Time until the next state, when applicable.
    float next_state_timer;
    
    //Is the mouse on top of a button?
    bool mouse_on_skip_button;
    bool mouse_on_back_button;
    bool mouse_on_ok_button;
    
    //The player currently choses this as the winning team.
    unsigned char chosen_team;
    
    //Team picker divisor's X coordinate.
    int picker_team_x;
    
    //Is the mouse on top of the team picker?
    bool mouse_down_on_team_picker;
    
    //Unclaimed turf picker's X coordinate.
    int picker_unclaimed_x;
    
    //Is the mouse on top of the unclaimed turf picker?
    bool mouse_down_on_unclaimed_picker;
    
    //Show the arena?
    bool show_arena;
    
    //Show the match's ink on top of the arena?
    bool show_ink;
    
    //Show the current text in a different style (written by the dev)?
    bool dev_text;
    
    //Player's chosen percentages.
    float player_percentages[3];
    
    //Player's score.
    float player_score;
    
    //The current committee comment.
    string committee_comment;
    
    //String with the current story script message.
    string cur_message;
    
    //Draw the current story script message's characters up to this one.
    size_t cur_message_char;
    
    //Time left until the next character is revealed.
    float cur_message_char_timer;
    
    //Current story script block.
    size_t cur_message_block;
    
    //Current confetti particles.
    vector<Confetto> confetti;
    
    //Judd's hop finishing Y coordinate.
    int judd_end_y;
    
    //Judd's hop timer.
    float judd_timer;
    
    //Opacity of the darkening effect on the analysis screen.
    unsigned char analysis_darken_opacity;
    
    void draw_textured_rectangle(
        const int x, const int y, const int w, const int h,
        ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR color,
        const unsigned char movement_pattern
    );
    void update_picker_x(
        int* var, const int mouse_value,
        const int bar_x, const int bar_w, const bool update_chosen_team,
        const bool mouse_value_is_delta
    );
    float ease_hop(const float n);
    void calculate_player_percentages();
    void calculate_player_score();
    void advance_story();
    
public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    explicit Gameplay(Game* game);
    ~Gameplay();
};


#endif //ifndef INCLUDED_GAMEPLAY_H
