#include <math.h>

#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "gameplay.h"
#include "utils.h"


Gameplay::Gameplay(Game* game) :
    Game_State(game),
    difficulty(DIFFICULTY_BEGINNER),
    sub_state(SUB_STATE_PICKING),
    next_state_timer(0),
    mouse_on_back_button(false),
    mouse_on_ok_button(false),
    chosen_team(TEAM_NONE),
    picker_team_x(0),
    mouse_down_on_team_picker(false),
    picker_unclaimed_x(0),
    mouse_down_on_unclaimed_picker(false) {
    
    
}


void Gameplay::load() {
    sub_state = SUB_STATE_PICKING;
    next_state_timer = 0;
    mouse_on_back_button = false;
    mouse_on_ok_button = false;
    mouse_down_on_team_picker = false;
    mouse_down_on_unclaimed_picker = false;
    chosen_team = TEAM_NONE;
    analysis_darken_opacity = 0;
    confetti.clear();
    
    if(game->chapter_to_load == 0) {
        difficulty = game->free_play_difficulty;
    } else {
        difficulty = game->cur_chapter.chapter_data->difficulty;
    }
    
    if(difficulty == DIFFICULTY_BEGINNER) {
        judd_end_y = PICKER_B_Y;
        
    } else if(difficulty == DIFFICULTY_INTERMEDIATE) {
        picker_team_x = PICKER_I_BAR_W / 2.0;
        judd_end_y = PICKER_I_Y;
        
    } else if(difficulty == DIFFICULTY_EXPERT) {
        picker_team_x = PICKER_E_TEAM_BAR_W / 2.0;
        picker_unclaimed_x = PICKER_E_NONE_BAR_W / 4.0;
        judd_end_y = PICKER_E_Y;
        
    }
    
    
    calculate_player_percentages();
}


void Gameplay::handle_mouse(ALLEGRO_EVENT ev) {

    if(sub_state == SUB_STATE_PICKING) {
    
        ALLEGRO_SYSTEM_MOUSE_CURSOR cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
        
        mouse_on_back_button =
            ev.mouse.x >= BACK_BUTTON_X &&
            ev.mouse.y >= BACK_BUTTON_Y &&
            ev.mouse.x <= BACK_BUTTON_X + BACK_BUTTON_W &&
            ev.mouse.y <= BACK_BUTTON_Y + BACK_BUTTON_H;
            
        mouse_on_ok_button =
            ev.mouse.x >= OK_BUTTON_X &&
            ev.mouse.y >= OK_BUTTON_Y &&
            ev.mouse.x <= OK_BUTTON_X + OK_BUTTON_W &&
            ev.mouse.y <= OK_BUTTON_Y + OK_BUTTON_H;
            
        if(mouse_on_ok_button || mouse_on_back_button) {
            cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK;
        }
        
        if(difficulty == DIFFICULTY_BEGINNER) {
        
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
            
        } else if(difficulty == DIFFICULTY_INTERMEDIATE) {
        
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
        
        calculate_player_percentages();
        
        if(
            mouse_on_ok_button && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
            chosen_team != TEAM_NONE
        ) {
            sub_state = SUB_STATE_CELEBRATING;
            for(size_t c = 0; c < N_CONFETTI * 0.7; ++c) {
                Confetto confetto;
                confetto.angle = randomf(0, M_PI * 2);
                confetto.color =
                    darken_color(
                        game->cur_chapter.ink_colors[chosen_team],
                        randomf(0.75, 1.0)
                    );
                confetto.pos =
                    Point(
                        randomi(0, WINDOW_WIDTH),
                        randomi(-WINDOW_HEIGHT, -Gameplay::Confetto::CONFETTO_SIZE)
                    );
                confetto.rotation_speed = randomf(0, M_PI * 2);
                confetto.speed =
                    Point(
                        randomf(-50, 50),
                        WINDOW_HEIGHT + randomf(-100, 100)
                    );
                confetti.push_back(confetto);
            }
            for(size_t c = 0; c < N_CONFETTI * 0.15; ++c) {
                Confetto confetto;
                confetto.angle = randomf(0, M_PI * 2);
                confetto.color =
                    darken_color(
                        game->cur_chapter.ink_colors[chosen_team],
                        randomf(0.75, 1.0)
                    );
                confetto.pos =
                    Point(
                        -(Gameplay::Confetto::CONFETTO_SIZE * 2),
                        randomi(0, WINDOW_HEIGHT * 0.3)
                    );
                confetto.rotation_speed = randomf(0, M_PI * 2);
                confetto.speed =
                    Point(
                        randomf(WINDOW_WIDTH, WINDOW_WIDTH * 2),
                        WINDOW_HEIGHT + randomf(-100, 100)
                    );
                confetti.push_back(confetto);
            }
            for(size_t c = 0; c < N_CONFETTI * 0.15; ++c) {
                Confetto confetto;
                confetto.angle = randomf(0, M_PI * 2);
                confetto.color =
                    darken_color(
                        game->cur_chapter.ink_colors[chosen_team],
                        randomf(0.75, 1.0)
                    );
                confetto.pos =
                    Point(
                        WINDOW_WIDTH + (Gameplay::Confetto::CONFETTO_SIZE * 2),
                        randomi(0, WINDOW_HEIGHT * 0.3)
                    );
                confetto.rotation_speed = randomf(0, M_PI * 2);
                confetto.speed =
                    Point(
                        randomf(-WINDOW_WIDTH, -(WINDOW_WIDTH * 2)),
                        WINDOW_HEIGHT + randomf(-100, 100)
                    );
                confetti.push_back(confetto);
            }
            judd_timer = JUDD_HOP_DURATION;
            next_state_timer = CELEBRATION_DURATION;
            cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
            calculate_player_score();
        }
        
        if(
            mouse_on_back_button && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
        ) {
            game->state_mgr.change_state(GAME_STATE_MAIN_MENU);
        }
        
        al_set_system_mouse_cursor(game->display, cursor);
        
    } else if(
        sub_state == SUB_STATE_ANALYSIS_FULL &&
        ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
    ) {
        if(game->chapter_to_load > 0) {
            game->chapter_to_load++;
        }
        //TODO last chapter
        //TODO only advance on victory condition
        game->state_mgr.change_state(GAME_STATE_LOADING);
        
    } else if(
        sub_state >= SUB_STATE_CELEBRATING &&
        sub_state <= SUB_STATE_ANALYSIS_2 &&
        ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
    ) {
        analysis_darken_opacity = ANALYSIS_DARKEN_VALUE;
        sub_state = SUB_STATE_ANALYSIS_FULL;
    }
}


void Gameplay::do_logic() {
    for(size_t c = 0; c < confetti.size(); ) {
        if(confetti[c].tick()) {
            confetti.erase(confetti.begin() + c);
        } else {
            ++c;
        }
    }
    
    if(next_state_timer > 0) {
        next_state_timer -= 1.0 / GAME_FPS;
        if(next_state_timer <= 0) {
            next_state_timer = 0;
            
            if(sub_state == SUB_STATE_CELEBRATING) {
                sub_state = SUB_STATE_ANALYSIS_FADE_IN;
                next_state_timer = ANALYSIS_FADE_DURATION;
                analysis_darken_opacity = 0;
                
            } else if(sub_state == SUB_STATE_ANALYSIS_FADE_IN) {
                sub_state = SUB_STATE_ANALYSIS_1;
                next_state_timer = ANALYSIS_DATA_DELAY;
                analysis_darken_opacity = ANALYSIS_DARKEN_VALUE;
                
            } else if(sub_state == SUB_STATE_ANALYSIS_1) {
                sub_state = SUB_STATE_ANALYSIS_2;
                next_state_timer = ANALYSIS_DATA_DELAY;
                
            } else if(sub_state == SUB_STATE_ANALYSIS_2) {
                sub_state = SUB_STATE_ANALYSIS_FULL;
                
            }
            
        }
    }
    
    if(sub_state >= SUB_STATE_CELEBRATING) {
        judd_timer -= 1.0 / GAME_FPS;
        judd_timer = max(0.0f, judd_timer);
    }
    
    if(sub_state == SUB_STATE_ANALYSIS_FADE_IN) {
        analysis_darken_opacity =
            (1 - (next_state_timer / ANALYSIS_FADE_DURATION)) *
            ANALYSIS_DARKEN_VALUE;
    }
}


void Gameplay::do_drawing() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    draw_textured_rectangle(
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        game->cur_chapter.background_bmp, al_map_rgb(255, 255, 255),
        false
    );
    al_draw_bitmap(
        game->cur_chapter.arena_bmp, WINDOW_WIDTH / 2.0 - game->cur_chapter.width / 2.0,
        4, 0
    );
    al_draw_tinted_bitmap(
        game->cur_chapter.result_bmp, al_map_rgba(255, 255, 255, 210),
        WINDOW_WIDTH / 2.0 - game->cur_chapter.width / 2.0, 4, 0
    );
    
    for(size_t c = 0; c < confetti.size(); ++c) {
        confetti[c].draw();
    }
    
    if(sub_state >= SUB_STATE_CELEBRATING) {
        game->draw_judd(
            WINDOW_WIDTH * 0.5,
            JUDD_START_Y - (JUDD_START_Y - judd_end_y) *
            ease_hop(1 - (judd_timer / JUDD_HOP_DURATION)),
            JUDD_SCALE, chosen_team == TEAM_2,
            game->cur_chapter.ink_colors[chosen_team]
        );
    }
    
    //TODO remove these debugging values
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255), 0, 8, 0,
        f2s(game->cur_chapter.real_percentages[TEAM_1]) + ";" +
        f2s(game->cur_chapter.real_percentages[TEAM_2]) + ";" +
        f2s(game->cur_chapter.real_percentages[TEAM_NONE]),
        0.5
    );
    
    if(difficulty == DIFFICULTY_BEGINNER) {
        draw_textured_rectangle(
            PICKER_B_TEAM_1_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            game->bmp_ink_effect,
            (
                chosen_team == TEAM_1 ?
                game->cur_chapter.ink_colors[TEAM_1] :
                darken_color(game->cur_chapter.ink_colors[TEAM_1], 0.5)
            ),
            (chosen_team == TEAM_1)
        );
        
        draw_textured_rectangle(
            PICKER_B_TEAM_2_BUTTON_X, PICKER_B_TEAM_BUTTON_Y,
            PICKER_B_TEAM_BUTTON_W, PICKER_B_TEAM_BUTTON_H,
            game->bmp_ink_effect,
            (
                chosen_team == TEAM_2 ?
                game->cur_chapter.ink_colors[TEAM_2] :
                darken_color(game->cur_chapter.ink_colors[TEAM_2], 0.5)
            ),
            (chosen_team == TEAM_2)
        );
        
        al_draw_bitmap(game->bmp_picker_b, PICKER_B_X, PICKER_B_Y, 0);
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = game->cur_chapter.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? game->bmp_button_k_selected : game->bmp_button_k_unselected),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    } else if(difficulty == DIFFICULTY_INTERMEDIATE) {
        draw_textured_rectangle(
            PICKER_I_BAR_X, PICKER_I_BAR_Y,
            picker_team_x, PICKER_I_BAR_H,
            game->bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                game->cur_chapter.ink_colors[TEAM_1] :
                darken_color(game->cur_chapter.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_I_BAR_X + picker_team_x, PICKER_I_BAR_Y,
            PICKER_I_BAR_W - picker_team_x, PICKER_I_BAR_H,
            game->bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                game->cur_chapter.ink_colors[TEAM_2] :
                darken_color(game->cur_chapter.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        al_draw_bitmap(game->bmp_picker_i, PICKER_I_X, PICKER_I_Y, 0);
        
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_I_BAR_X + 8, PICKER_I_BAR_Y + 21, 0,
            f2s(player_percentages[TEAM_1]) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_I_BAR_X + PICKER_I_BAR_W - 8,
            PICKER_I_BAR_Y + 21,
            ALLEGRO_ALIGN_RIGHT,
            f2s(player_percentages[TEAM_2]) + "%"
        );
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = game->cur_chapter.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? game->bmp_button_k_selected : game->bmp_button_k_unselected),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    } else if(difficulty == DIFFICULTY_EXPERT) {
        draw_textured_rectangle(
            PICKER_E_TEAM_BAR_X, PICKER_E_TEAM_BAR_Y,
            picker_team_x, PICKER_E_TEAM_BAR_H,
            game->bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                game->cur_chapter.ink_colors[TEAM_1] :
                darken_color(game->cur_chapter.ink_colors[TEAM_1], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_E_TEAM_BAR_X + picker_team_x, PICKER_E_TEAM_BAR_Y,
            PICKER_E_TEAM_BAR_W - picker_team_x, PICKER_E_TEAM_BAR_H,
            game->bmp_ink_effect,
            (
                chosen_team != TEAM_NONE ?
                game->cur_chapter.ink_colors[TEAM_2] :
                darken_color(game->cur_chapter.ink_colors[TEAM_2], 0.5)
            ),
            chosen_team != TEAM_NONE
        );
        
        draw_textured_rectangle(
            PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_Y,
            picker_unclaimed_x, PICKER_E_NONE_BAR_H,
            game->bmp_checkerboard, al_map_rgb(128, 128, 128), false
        );
        
        al_draw_bitmap(game->bmp_picker_e, PICKER_E_X, PICKER_E_Y, 0);
        
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_TEAM_BAR_X + 8, PICKER_E_TEAM_BAR_Y + 21,
            0, f2s(player_percentages[TEAM_1]) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_TEAM_BAR_X + PICKER_E_TEAM_BAR_W - 8,
            PICKER_E_TEAM_BAR_Y + 21,
            ALLEGRO_ALIGN_RIGHT,
            f2s(player_percentages[TEAM_2]) + "%"
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            PICKER_E_NONE_BAR_X + 8, PICKER_E_NONE_BAR_Y + 20,
            0, f2s(player_percentages[TEAM_NONE]) + "%"
        );
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != TEAM_NONE) {
            ok_button_tint = game->cur_chapter.ink_colors[chosen_team];
        }
        al_draw_tinted_bitmap(
            (mouse_on_ok_button ? game->bmp_button_k_selected : game->bmp_button_k_unselected),
            ok_button_tint, OK_BUTTON_X, OK_BUTTON_Y, 0
        );
        
    }
    
    al_draw_bitmap(
        (mouse_on_back_button ? game->bmp_button_l_selected : game->bmp_button_l_unselected),
        BACK_BUTTON_X, BACK_BUTTON_Y, 0
    );
    
    if(sub_state >= SUB_STATE_ANALYSIS_FADE_IN) {
        al_draw_filled_rectangle(
            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
            al_map_rgba(0, 0, 0, analysis_darken_opacity)
        );
    }
    
    if(sub_state >= SUB_STATE_ANALYSIS_1) {
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_LEFT_TEAM_X, ANALYSIS_HEADER_ROW_Y,
            ALLEGRO_ALIGN_CENTER, "LEFT TEAM", 0.5
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_RIGHT_TEAM_X, ANALYSIS_HEADER_ROW_Y,
            ALLEGRO_ALIGN_CENTER, "RIGHT TEAM", 0.5
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_UNCLAIMED_X, ANALYSIS_HEADER_ROW_Y,
            ALLEGRO_ALIGN_CENTER, "UNCLAIMED", 0.5
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_HEADER_COLUMN_X, ANALYSIS_YOUR_DECISION_Y,
            ALLEGRO_ALIGN_RIGHT, "YOUR DECISION:", 0.5
        );
        if(chosen_team == 0) {
            al_draw_tinted_bitmap(
                game->bmp_splash, game->cur_chapter.ink_colors[chosen_team],
                ANALYSIS_LEFT_TEAM_X -
                al_get_bitmap_width(game->bmp_splash) * 0.5,
                ANALYSIS_YOUR_DECISION_Y -
                al_get_bitmap_height(game->bmp_splash) * 0.5,
                0
            );
        } else {
            al_draw_tinted_bitmap(
                game->bmp_splash, game->cur_chapter.ink_colors[chosen_team],
                ANALYSIS_RIGHT_TEAM_X -
                al_get_bitmap_width(game->bmp_splash) * 0.5,
                ANALYSIS_YOUR_DECISION_Y -
                al_get_bitmap_height(game->bmp_splash) * 0.5,
                0
            );
        }
        if(difficulty == DIFFICULTY_BEGINNER) {
            draw_shadowed_text(
                game->font, al_map_rgb(255, 255, 255),
                ANALYSIS_LEFT_TEAM_X, ANALYSIS_YOUR_DECISION_Y,
                ALLEGRO_ALIGN_CENTER,
                (chosen_team == TEAM_1 ? "WINS" : "LOSES"), 0.8
            );
        } else {
            draw_shadowed_text(
                game->font, al_map_rgb(255, 255, 255),
                ANALYSIS_LEFT_TEAM_X, ANALYSIS_YOUR_DECISION_Y,
                ALLEGRO_ALIGN_CENTER,
                f2s(player_percentages[TEAM_1]) + "%", 0.8
            );
        }
        if(difficulty == DIFFICULTY_BEGINNER) {
            draw_shadowed_text(
                game->font, al_map_rgb(255, 255, 255),
                ANALYSIS_RIGHT_TEAM_X, ANALYSIS_YOUR_DECISION_Y,
                ALLEGRO_ALIGN_CENTER,
                (chosen_team == TEAM_2 ? "WINS" : "LOSES"), 0.8
            );
        } else {
            draw_shadowed_text(
                game->font, al_map_rgb(255, 255, 255),
                ANALYSIS_RIGHT_TEAM_X, ANALYSIS_YOUR_DECISION_Y,
                ALLEGRO_ALIGN_CENTER,
                f2s(player_percentages[TEAM_2]) + "%", 0.8
            );
        }
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_UNCLAIMED_X, ANALYSIS_YOUR_DECISION_Y,
            ALLEGRO_ALIGN_CENTER,
            (
                difficulty == DIFFICULTY_EXPERT ?
                f2s(player_percentages[TEAM_NONE]) + "%" :
                "---"
            ), 0.8
        );
        
    }
    
    if(sub_state >= SUB_STATE_ANALYSIS_2) {
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_HEADER_COLUMN_X, ANALYSIS_REAL_Y,
            ALLEGRO_ALIGN_RIGHT, "REAL RESULTS:", 0.5
        );
        if(
            game->cur_chapter.real_percentages[TEAM_1] >
            game->cur_chapter.real_percentages[TEAM_2]
        ) {
            al_draw_tinted_bitmap(
                game->bmp_splash, game->cur_chapter.ink_colors[TEAM_1],
                ANALYSIS_LEFT_TEAM_X -
                al_get_bitmap_width(game->bmp_splash) * 0.5,
                ANALYSIS_REAL_Y -
                al_get_bitmap_height(game->bmp_splash) * 0.5,
                0
            );
        } else {
            al_draw_tinted_bitmap(
                game->bmp_splash, game->cur_chapter.ink_colors[TEAM_2],
                ANALYSIS_RIGHT_TEAM_X -
                al_get_bitmap_width(game->bmp_splash) * 0.5,
                ANALYSIS_REAL_Y -
                al_get_bitmap_height(game->bmp_splash) * 0.5,
                0
            );
        }
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_LEFT_TEAM_X, ANALYSIS_REAL_Y,
            ALLEGRO_ALIGN_CENTER,
            f2s(game->cur_chapter.real_percentages[TEAM_1]) + "%", 0.8
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_RIGHT_TEAM_X, ANALYSIS_REAL_Y,
            ALLEGRO_ALIGN_CENTER,
            f2s(game->cur_chapter.real_percentages[TEAM_2]) + "%", 0.8
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_UNCLAIMED_X, ANALYSIS_REAL_Y,
            ALLEGRO_ALIGN_CENTER,
            f2s(game->cur_chapter.real_percentages[TEAM_NONE]) + "%", 0.8
        );
        
    }
    
    if(sub_state >= SUB_STATE_ANALYSIS_FULL) {
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_SCORE_X, ANALYSIS_SCORE_Y,
            ALLEGRO_ALIGN_CENTER,
            "YOUR SCORE: " + i2s(round(player_score))
        );
        
    }
    
    al_flip_display();
}


void Gameplay::unload() {

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


void Gameplay::calculate_player_percentages() {
    if(difficulty == DIFFICULTY_BEGINNER) {
        return;
        
    } else if(difficulty == DIFFICULTY_INTERMEDIATE) {
        player_percentages[TEAM_NONE] = 0;
        player_percentages[TEAM_1] =
            (picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - game->cur_chapter.real_percentages[TEAM_NONE] / 100.0);
        player_percentages[TEAM_2] =
            (1 - picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - game->cur_chapter.real_percentages[TEAM_NONE] / 100.0);
            
    } else {
        player_percentages[TEAM_NONE] =
            picker_unclaimed_x / (float) PICKER_E_NONE_BAR_W;
        player_percentages[TEAM_1] =
            (picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - player_percentages[TEAM_NONE]);
        player_percentages[TEAM_2] =
            (1 - picker_team_x / (float) PICKER_E_TEAM_BAR_W) *
            (1 - player_percentages[TEAM_NONE]);
            
    }
    
    player_percentages[TEAM_NONE] *= 100;
    player_percentages[TEAM_1] *= 100;
    player_percentages[TEAM_2] *= 100;
}


void Gameplay::calculate_player_score() {
    if(difficulty == DIFFICULTY_BEGINNER) {
        unsigned char real_winner =
            game->cur_chapter.real_percentages[TEAM_1] >
            game->cur_chapter.real_percentages[TEAM_2] ? TEAM_1 : TEAM_2;
        player_score = (real_winner == chosen_team ? 100 : 0);
        return;
    }
    
    float accuracies[3];
    for(unsigned char t = 0; t < 3; ++t) {
        accuracies[t] =
            100 -
            fabs(game->cur_chapter.real_percentages[t] - player_percentages[t]);
    }
    
    //Due to rounding problems, for the team turf,
    //use the best match of the two.
    player_score = max(accuracies[0], accuracies[1]);
    
    if(difficulty == DIFFICULTY_EXPERT) {
        //Expert difficulty accuracy =
        //(unclaimed turf accuracy + claimed turf split accuracy) / 2.
        player_score = (player_score + accuracies[2]) / 2;
    }
    
    //Due to rounding problems, let's be generous and turn those
    //"basically perfect"s into actual perfects.
    if(player_score >= 99.9) player_score = 100;
    
    player_score = (player_score - 50) * 2.0;
    player_score = max(0.0f, player_score);
}


float Gameplay::ease_hop(const float n) {
    //From http://i.stack.imgur.com/vqA2E.jpg
    return n * (n * (4 * n - 9) + 6);
}


bool Gameplay::Confetto::tick() {
    pos += speed * (1.0 / GAME_FPS);
    angle += rotation_speed * 1.0 / GAME_FPS;
    if(pos.y > WINDOW_HEIGHT + CONFETTO_SIZE * 2) {
        return true;
    }
    return false;
}


void Gameplay::Confetto::draw() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, angle);
    al_translate_transform(&transform, pos.x, pos.y);
    ALLEGRO_TRANSFORM old_transform;
    al_copy_transform(&old_transform, al_get_current_transform());
    al_use_transform(&transform); {
        al_draw_filled_rectangle(
            -(CONFETTO_SIZE * 0.5), -(CONFETTO_SIZE * 0.5),
            (CONFETTO_SIZE * 0.5), (CONFETTO_SIZE * 0.5),
            color
        );
    } al_use_transform(&old_transform);
}
