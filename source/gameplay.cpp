#include "game.h"
#include "gameplay.h"
#include "utils.h"


Gameplay::Gameplay(Game* game) :
    Game_State(game),
    game_mode(GAME_MODE_BEGINNER),
    mouse_on_ok_button(false),
    chosen_team(TEAM_NONE),
    picker_team_x(0),
    mouse_down_on_team_picker(false),
    picker_unclaimed_x(0),
    mouse_down_on_unclaimed_picker(false),
    bmp_button_1(nullptr),
    bmp_button_2(nullptr),
    bmp_picker_1(nullptr),
    bmp_picker_2(nullptr),
    bmp_picker_3(nullptr),
    bmp_ink_effect(nullptr) {
    
    
}


void Gameplay::load() {
    cur_arena.load();
    cur_arena.do_match();
    cur_arena.calculate_real_percentages();
    cur_arena.render();
    
    bmp_button_1 = game->bmp_mgr.get_bitmap(BMP_BUTTON_1);
    bmp_button_2 = game->bmp_mgr.get_bitmap(BMP_BUTTON_2);
    bmp_picker_1 = game->bmp_mgr.get_bitmap(BMP_PICKER_1);
    bmp_picker_2 = game->bmp_mgr.get_bitmap(BMP_PICKER_2);
    bmp_picker_3 = game->bmp_mgr.get_bitmap(BMP_PICKER_3);
    bmp_ink_effect = game->bmp_mgr.get_bitmap(BMP_INK_EFFECT);
    
    if(game_mode == GAME_MODE_INTERMEDIATE) {
        picker_team_x = PICKER_I_BAR_W / 2.0;
    } else if(game_mode == GAME_MODE_EXPERT) {
        picker_team_x = PICKER_E_TEAM_BAR_W / 2.0;
        picker_unclaimed_x = PICKER_E_NONE_BAR_W / 4.0;
    }
}


void Gameplay::handle_mouse(ALLEGRO_EVENT ev) {
    mouse_on_ok_button =
        ev.mouse.x >= OK_BUTTON_X &&
        ev.mouse.y >= OK_BUTTON_Y &&
        ev.mouse.x <= OK_BUTTON_X + OK_BUTTON_W &&
        ev.mouse.y <= OK_BUTTON_Y + OK_BUTTON_H;
        
    if(game_mode == GAME_MODE_BEGINNER) {
    
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(
                ev.mouse.y >= PICKER_B_TEAM_BUTTON_Y &&
                ev.mouse.y <= PICKER_B_TEAM_BUTTON_Y + PICKER_B_TEAM_BUTTON_H
            ) {
                if(
                    ev.mouse.x >= PICKER_B_TEAM_1_BUTTON_X &&
                    ev.mouse.x <= PICKER_B_TEAM_1_BUTTON_X +
                    PICKER_B_TEAM_BUTTON_W
                ) {
                    chosen_team = TEAM_1;
                    
                } else if(
                    ev.mouse.x >= PICKER_B_TEAM_2_BUTTON_X &&
                    ev.mouse.x <= PICKER_B_TEAM_2_BUTTON_X +
                    PICKER_B_TEAM_BUTTON_W
                ) {
                    chosen_team = TEAM_2;
                    
                }
            }
        }
        
    } else if(game_mode == GAME_MODE_INTERMEDIATE) {
    
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(
                ev.mouse.x >= PICKER_I_X && ev.mouse.y >= PICKER_I_BAR_Y &&
                ev.mouse.x <= PICKER_I_X + PICKER_I_W &&
                ev.mouse.y <= PICKER_I_BAR_Y + PICKER_I_BAR_H
            ) {
                mouse_down_on_team_picker = true;
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_I_BAR_X, PICKER_I_BAR_W, true
                );
            }
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_down_on_team_picker = false;
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if(mouse_down_on_team_picker) {
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_I_BAR_X, PICKER_I_BAR_W, true
                );
            }
            
        }
        
    } else {
    
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(
                ev.mouse.x >= PICKER_E_X &&
                ev.mouse.y >= PICKER_E_TEAM_BAR_Y &&
                ev.mouse.x <= PICKER_E_X + PICKER_E_W &&
                ev.mouse.y <= PICKER_E_TEAM_BAR_Y + PICKER_E_TEAM_BAR_H
            ) {
                mouse_down_on_team_picker = true;
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_W, true
                );
                
            } else if(
                ev.mouse.x >= PICKER_E_X &&
                ev.mouse.y >= PICKER_E_NONE_BAR_Y &&
                ev.mouse.x <= PICKER_E_X + PICKER_E_W &&
                ev.mouse.y <= PICKER_E_NONE_BAR_Y + PICKER_E_NONE_BAR_H
            ) {
                mouse_down_on_unclaimed_picker = true;
                update_picker_x(
                    &picker_unclaimed_x, ev.mouse.x,
                    PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_W, false
                );
                
            }
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_down_on_team_picker = false;
            mouse_down_on_unclaimed_picker = false;
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if(mouse_down_on_team_picker) {
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_W, true
                );
            } else if(mouse_down_on_unclaimed_picker) {
                update_picker_x(
                    &picker_unclaimed_x, ev.mouse.x,
                    PICKER_E_NONE_BAR_X, PICKER_E_TEAM_BAR_W, false
                );
            }
            
        }
        
    }
}


void Gameplay::do_logic() {

}


void Gameplay::do_drawing() {
    al_set_target_backbuffer(game->display);
    al_clear_to_color(al_map_rgb(16, 32, 16));
    
    al_draw_bitmap(cur_arena.background_bmp, 0, 0, 0);
    al_draw_bitmap(cur_arena.result_bmp, 0, 0, 0);
    
    //TODO remove these debugging values
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 0, 0, f2s(cur_arena.real_percentages[TEAM_1]).c_str());
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 8, 0, f2s(cur_arena.real_percentages[TEAM_2]).c_str());
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 16, 0, f2s(cur_arena.real_percentages[TEAM_NONE]).c_str());
    
    if(game_mode == GAME_MODE_BEGINNER) {
        draw_ink_button(
            PICKER_B_TEAM_1_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            (
                chosen_team == TEAM_1 ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            (chosen_team == TEAM_1)
        );
        
        draw_ink_button(
            PICKER_B_TEAM_2_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            (
                chosen_team == TEAM_2 ?
                cur_arena.ink_colors[TEAM_2] :
                darken_color(cur_arena.ink_colors[TEAM_2], 0.5)
            ),
            (chosen_team == TEAM_2)
        );
        
        al_draw_bitmap(bmp_picker_1, PICKER_B_X, PICKER_B_Y, 0);
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = cur_arena.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? bmp_button_2 : bmp_button_1),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    } else if(game_mode == GAME_MODE_INTERMEDIATE) {
        draw_ink_button(
            PICKER_I_BAR_X, PICKER_I_BAR_Y,
            picker_team_x, PICKER_I_BAR_H,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_ink_button(
            PICKER_I_BAR_X + picker_team_x, PICKER_I_BAR_Y,
            PICKER_I_BAR_W - picker_team_x, PICKER_I_BAR_H,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_2] :
                darken_color(cur_arena.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        al_draw_bitmap(bmp_picker_2, PICKER_I_X, PICKER_I_Y, 0);
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = cur_arena.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? bmp_button_2 : bmp_button_1),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    } else if(game_mode == GAME_MODE_EXPERT) {
        draw_ink_button(
            PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_Y,
            picker_team_x, PICKER_E_TEAM_BAR_H,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_ink_button(
            PICKER_E_TEAM_BAR_X + picker_team_x, PICKER_E_TEAM_BAR_Y,
            PICKER_E_TEAM_BAR_W - picker_team_x, PICKER_E_TEAM_BAR_H,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_2] :
                darken_color(cur_arena.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        al_draw_filled_rectangle(
            PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_Y,
            PICKER_E_NONE_BAR_X + picker_unclaimed_x,
            PICKER_E_NONE_BAR_Y + PICKER_E_NONE_BAR_H,
            al_map_rgb(128, 128, 128)
        );
        
        al_draw_bitmap(bmp_picker_3, PICKER_E_X, PICKER_E_Y, 0);
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = cur_arena.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? bmp_button_2 : bmp_button_1),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    }
    
    al_flip_display();
}


void Gameplay::unload() {
    al_save_bitmap("bmp.png", cur_arena.background_bmp); //TODO
}


void Gameplay::draw_ink_button(
    const int x, const int y, const int w, const int h,
    ALLEGRO_COLOR color, const bool moving
) {
    ALLEGRO_VERTEX vertexes[4];
    
    for(unsigned char v = 0; v < 4; ++v) {
        vertexes[v].z = 0;
        vertexes[v].color = color;
    }
    
    vertexes[0].x = x;
    vertexes[0].y = y;
    vertexes[0].u = x + (moving ? -(game->time_spent * 10) : 0);
    vertexes[0].v = y + (moving ? -(game->time_spent * 20) : 0);
    
    vertexes[1].x = vertexes[0].x + w;
    vertexes[1].y = vertexes[0].y;
    vertexes[1].u = vertexes[0].u + w;
    vertexes[1].v = vertexes[0].v;
    
    vertexes[2].x = vertexes[0].x + w;
    vertexes[2].y = vertexes[0].y + h;
    vertexes[2].u = vertexes[0].u + w;
    vertexes[2].v = vertexes[0].v + h;
    
    vertexes[3].x = vertexes[0].x;
    vertexes[3].y = vertexes[0].y + h;
    vertexes[3].u = vertexes[0].u;
    vertexes[3].v = vertexes[0].v + h;
    
    al_draw_prim(
        vertexes, NULL, bmp_ink_effect, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN
    );
}


void Gameplay::update_picker_x(
    int* var, const int mouse_x,
    const int bar_x, const int bar_w, const bool update_chosen_team
) {
    *var = mouse_x - bar_x;
    *var = max(0, *var);
    *var = min(*var, bar_w);
    if(update_chosen_team) {
        chosen_team = *var < bar_w / 2.0 ? 1 : 0;
    }
}
