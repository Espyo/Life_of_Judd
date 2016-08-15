#include <allegro5/allegro_primitives.h>

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
    
    game_mode = GAME_MODE_BEGINNER; //TODO
    
    bmp_button_1 = game->bmp_mgr.get_bitmap(BMP_BUTTON_1);
    bmp_button_2 = game->bmp_mgr.get_bitmap(BMP_BUTTON_2);
    bmp_picker_1 = game->bmp_mgr.get_bitmap(BMP_PICKER_1);
    bmp_picker_2 = game->bmp_mgr.get_bitmap(BMP_PICKER_2);
    bmp_picker_3 = game->bmp_mgr.get_bitmap(BMP_PICKER_3);
    bmp_ink_effect = game->bmp_mgr.get_bitmap(BMP_INK_EFFECT);
    bmp_checkerboard = game->bmp_mgr.get_bitmap(BMP_CHECKERBOARD);
    
    if(game_mode == GAME_MODE_INTERMEDIATE) {
        picker_team_x = PICKER_I_BAR_W / 2.0;
    } else if(game_mode == GAME_MODE_EXPERT) {
        picker_team_x = PICKER_E_TEAM_BAR_W / 2.0;
        picker_unclaimed_x = PICKER_E_NONE_BAR_W / 4.0;
    }
}


void Gameplay::handle_mouse(ALLEGRO_EVENT ev) {
    ALLEGRO_SYSTEM_MOUSE_CURSOR cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
    
    mouse_on_ok_button =
        ev.mouse.x >= OK_BUTTON_X &&
        ev.mouse.y >= OK_BUTTON_Y &&
        ev.mouse.x <= OK_BUTTON_X + OK_BUTTON_W &&
        ev.mouse.y <= OK_BUTTON_Y + OK_BUTTON_H;
        
    if(mouse_on_ok_button) {
        cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK;
    }
    
    if(game_mode == GAME_MODE_BEGINNER) {
    
        bool mouse_on_button_1 = false;
        bool mouse_on_button_2 = false;
        
        if(
            ev.mouse.y >= PICKER_B_TEAM_BUTTON_Y &&
            ev.mouse.y <= PICKER_B_TEAM_BUTTON_Y + PICKER_B_TEAM_BUTTON_H
        ) {
            if(
                ev.mouse.x >= PICKER_B_TEAM_1_BUTTON_X &&
                ev.mouse.x <= PICKER_B_TEAM_1_BUTTON_X +
                PICKER_B_TEAM_BUTTON_W
            ) {
                mouse_on_button_1 = true;
                
            } else if(
                ev.mouse.x >= PICKER_B_TEAM_2_BUTTON_X &&
                ev.mouse.x <= PICKER_B_TEAM_2_BUTTON_X +
                PICKER_B_TEAM_BUTTON_W
            ) {
                mouse_on_button_2 = true;
                
            }
        }
        
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouse_on_button_1) {
                chosen_team = TEAM_1;
            } else if(mouse_on_button_2) {
                chosen_team = TEAM_2;
            }
        }
        
        if(mouse_on_button_1 || mouse_on_button_2) {
            cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK;
        }
        
    } else if(game_mode == GAME_MODE_INTERMEDIATE) {
    
        bool mouse_on_bar =
            ev.mouse.x >= PICKER_I_X && ev.mouse.y >= PICKER_I_BAR_Y &&
            ev.mouse.x <= PICKER_I_X + PICKER_I_W &&
            ev.mouse.y <= PICKER_I_BAR_Y + PICKER_I_BAR_H;
            
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouse_on_bar) {
                mouse_down_on_team_picker = true;
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_I_BAR_X, PICKER_I_BAR_W, true, false
                );
            }
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_down_on_team_picker = false;
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if(mouse_down_on_team_picker) {
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_I_BAR_X, PICKER_I_BAR_W, true, false
                );
            }
            
            if(mouse_on_bar) {
                cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE;
                if(ev.mouse.dz != 0 && !mouse_down_on_team_picker) {
                    update_picker_x(
                        &picker_team_x, ev.mouse.dz,
                        PICKER_I_BAR_X, PICKER_I_BAR_W, true, true
                    );
                }
            }
            
        }
        
    } else {
    
        bool mouse_on_team_bar =
            ev.mouse.x >= PICKER_E_X &&
            ev.mouse.y >= PICKER_E_TEAM_BAR_Y &&
            ev.mouse.x <= PICKER_E_X + PICKER_E_W &&
            ev.mouse.y <= PICKER_E_TEAM_BAR_Y + PICKER_E_TEAM_BAR_H;
        bool mouse_on_unclaimed_bar =
            ev.mouse.x >= PICKER_E_X &&
            ev.mouse.y >= PICKER_E_NONE_BAR_Y &&
            ev.mouse.x <= PICKER_E_X + PICKER_E_W &&
            ev.mouse.y <= PICKER_E_NONE_BAR_Y + PICKER_E_NONE_BAR_H;
            
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouse_on_team_bar) {
                mouse_down_on_team_picker = true;
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_W, true, false
                );
                
            } else if(mouse_on_unclaimed_bar) {
                mouse_down_on_unclaimed_picker = true;
                update_picker_x(
                    &picker_unclaimed_x, ev.mouse.x,
                    PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_W, false, false
                );
                
            }
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_down_on_team_picker = false;
            mouse_down_on_unclaimed_picker = false;
            
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if(mouse_down_on_team_picker) {
                update_picker_x(
                    &picker_team_x, ev.mouse.x,
                    PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_W, true, false
                );
            } else if(mouse_down_on_unclaimed_picker) {
                update_picker_x(
                    &picker_unclaimed_x, ev.mouse.x,
                    PICKER_E_NONE_BAR_X, PICKER_E_TEAM_BAR_W, false, false
                );
            }
            
            if(mouse_on_team_bar) {
                cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE;
                if(ev.mouse.dz != 0 && !mouse_down_on_team_picker) {
                    update_picker_x(
                        &picker_team_x, ev.mouse.dz,
                        PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_W, true, true
                    );
                }
                
            } else if(mouse_on_unclaimed_bar) {
                cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE;
                if(ev.mouse.dz != 0 && !mouse_down_on_unclaimed_picker) {
                    update_picker_x(
                        &picker_unclaimed_x, ev.mouse.dz,
                        PICKER_E_NONE_BAR_X, PICKER_E_TEAM_BAR_W, false, true
                    );
                }
            }
            
        }
        
    }
    
    al_set_system_mouse_cursor(game->display, cursor);
}


void Gameplay::do_logic() {

}


void Gameplay::do_drawing() {
    al_set_target_backbuffer(game->display);
    al_clear_to_color(al_map_rgb(16, 32, 16));
    
    draw_textured_rectangle(
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        cur_arena.background_bmp, al_map_rgb(255, 255, 255),
        false
    );
    al_draw_bitmap(
        cur_arena.arena_bmp, WINDOW_WIDTH / 2.0 - cur_arena.width / 2.0,
        4, 0
    );
    al_draw_bitmap(
        cur_arena.result_bmp, WINDOW_WIDTH / 2.0 - cur_arena.width / 2.0,
        4, 0
    );
    
    //TODO remove these debugging values
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255), 0, 0, 0,
        f2s(cur_arena.real_percentages[TEAM_1]) + ";" +
        f2s(cur_arena.real_percentages[TEAM_2]) + ";" +
        f2s(cur_arena.real_percentages[TEAM_NONE]),
        0.5
    );
    
    if(game_mode == GAME_MODE_BEGINNER) {
        draw_textured_rectangle(
            PICKER_B_TEAM_1_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            bmp_ink_effect,
            (
                chosen_team == TEAM_1 ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            (chosen_team == TEAM_1)
        );
        
        draw_textured_rectangle(
            PICKER_B_TEAM_2_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            bmp_ink_effect,
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
        draw_textured_rectangle(
            PICKER_I_BAR_X, PICKER_I_BAR_Y,
            picker_team_x, PICKER_I_BAR_H,
            bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_I_BAR_X + picker_team_x, PICKER_I_BAR_Y,
            PICKER_I_BAR_W - picker_team_x, PICKER_I_BAR_H,
            bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_2] :
                darken_color(cur_arena.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        al_draw_bitmap(bmp_picker_2, PICKER_I_X, PICKER_I_Y, 0);
        
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_I_BAR_X + 8, PICKER_I_BAR_Y + 8, 0,
            f2s((picker_team_x / (float) PICKER_I_BAR_W) * 100) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_I_BAR_X + PICKER_I_BAR_W - 8, PICKER_I_BAR_Y + 8,
            ALLEGRO_ALIGN_RIGHT,
            f2s((1 - picker_team_x / (float) PICKER_I_BAR_W) * 100) + "%"
        );
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = cur_arena.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? bmp_button_2 : bmp_button_1),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    } else if(game_mode == GAME_MODE_EXPERT) {
        draw_textured_rectangle(
            PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_Y,
            picker_team_x, PICKER_E_TEAM_BAR_H,
            bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_1] :
                darken_color(cur_arena.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_E_TEAM_BAR_X + picker_team_x, PICKER_E_TEAM_BAR_Y,
            PICKER_E_TEAM_BAR_W - picker_team_x, PICKER_E_TEAM_BAR_H,
            bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                cur_arena.ink_colors[TEAM_2] :
                darken_color(cur_arena.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_Y,
            picker_unclaimed_x, PICKER_E_NONE_BAR_H,
            bmp_checkerboard, al_map_rgb(128, 128, 128), false
        );
        
        al_draw_bitmap(bmp_picker_3, PICKER_E_X, PICKER_E_Y, 0);
        
        float unclaimed_ratio =
            picker_unclaimed_x / (float) PICKER_E_NONE_BAR_W;
        float team_1_ratio =
            (picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - unclaimed_ratio);
        float team_2_ratio =
            (1 - picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - unclaimed_ratio);
            
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_TEAM_BAR_X + 8, PICKER_E_TEAM_BAR_Y + 8, 0,
            f2s(team_1_ratio * 100) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_TEAM_BAR_X + PICKER_E_TEAM_BAR_W - 8,
            PICKER_E_TEAM_BAR_Y + 8,
            ALLEGRO_ALIGN_RIGHT,
            f2s(team_2_ratio * 100) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_NONE_BAR_X + 8, PICKER_E_NONE_BAR_Y + 8, 0,
            f2s(unclaimed_ratio * 100) + "%"
        );
        
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
    al_save_bitmap("bmp.png", cur_arena.arena_bmp); //TODO
}


void Gameplay::draw_textured_rectangle(
    const int x, const int y, const int w, const int h,
    ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR color, const bool moving
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
        vertexes, NULL, bmp, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN
    );
}


void Gameplay::update_picker_x(
    int* var, const int mouse_value,
    const int bar_x, const int bar_w, const bool update_chosen_team,
    const bool mouse_value_is_delta
) {
    int mouse_x;
    if(mouse_value_is_delta) {
        mouse_x = bar_x + *var + mouse_value;
    } else {
        mouse_x = mouse_value;
    }
    
    *var = mouse_x - bar_x;
    *var = max(0, *var);
    *var = min(*var, bar_w);
    if(update_chosen_team) {
        float p = *var / (float) bar_w;
        if(p == 0.5) {
            chosen_team = 2;
        } else if(p < 0.5) {
            chosen_team = 1;
        } else {
            chosen_team = 0;
        }
    }
}
