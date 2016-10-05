#include <math.h>

#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "gameplay.h"
#include "utils.h"


Gameplay::Gameplay(Game* game) :
    Game_State(game),
    difficulty(DIFFICULTY_BEGINNER),
    sub_state(SUB_STATE_STORY_WRITING),
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
    next_state_timer = 0;
    mouse_on_back_button = false;
    mouse_on_ok_button = false;
    mouse_down_on_team_picker = false;
    mouse_down_on_unclaimed_picker = false;
    chosen_team = TEAM_NONE;
    analysis_darken_opacity = 0;
    confetti.clear();
    cur_message.clear();
    cur_message_char = 0;
    cur_message_char_timer = 0;
    cur_message_block = 0;
    
    dev_text = false;
    if(game->chapter_to_load == 0) {
        //Free play.
        sub_state = SUB_STATE_PICKING;
        show_arena = true;
        show_ink = true;
        difficulty = game->free_play_difficulty;
    } else {
        //Story mode.
        show_arena = false;
        show_ink = false;
        sub_state = SUB_STATE_STORY_WRITING;
        difficulty = game->cur_chapter.chapter_data->difficulty;
        cur_message = game->cur_chapter.chapter_data->story[0];
        cur_message_block = 0;
        cur_message_char = 0;
        cur_message_char_timer = MESSAGE_CHAR_INTERVAL;
        al_set_system_mouse_cursor(
            game->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK
        );
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

    if(
        sub_state == SUB_STATE_STORY_WRITING ||
        sub_state == SUB_STATE_STORY_WAITING
    ) {
        mouse_on_skip_button =
            ev.mouse.x >= SKIP_BUTTON_X &&
            ev.mouse.x <= SKIP_BUTTON_X + SKIP_BUTTON_W &&
            ev.mouse.y >= SKIP_BUTTON_Y &&
            ev.mouse.y <= SKIP_BUTTON_Y + SKIP_BUTTON_H;
    }
    
    if(sub_state == SUB_STATE_STORY_WRITING) {
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouse_on_skip_button) {
                sub_state = SUB_STATE_PICKING;
                show_arena = true;
                show_ink = true;
            } else {
                cur_message_char = cur_message.size() - 1;
            }
        }
        
    } else if(sub_state == SUB_STATE_STORY_WAITING) {
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouse_on_skip_button) {
                sub_state = SUB_STATE_PICKING;
                show_arena = true;
                show_ink = true;
            } else {
                advance_story();
            }
        }
        
    }
    
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
            
        if(
            (mouse_on_ok_button && chosen_team != TEAM_NONE) ||
            mouse_on_back_button
        ) {
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
                        randomi(-WINDOW_HEIGHT, -Gameplay::Confetto::CONFETTO_W)
                    );
                confetto.rotation_speed = randomf(M_PI * 2, M_PI * 4);
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
                        -(Gameplay::Confetto::CONFETTO_W * 2),
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
                        WINDOW_WIDTH + (Gameplay::Confetto::CONFETTO_W * 2),
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
            if(game->chapter_to_load != 0) {
                if(
                    player_score >
                    game->high_scores[game->chapter_to_load - 1]
                ) {
                    game->high_scores[game->chapter_to_load - 1] = player_score;
                    game->save_save_data();
                }
            }
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
            //Story mode.
            if(
                player_score >= PASSING_SCORE &&
                game->chapter_to_load < game->all_chapter_data.size()
            ) {
                game->chapter_to_load++;
                game->state_mgr.change_state(GAME_STATE_LOADING);
                
            } else {
                game->state_mgr.change_state(GAME_STATE_MAIN_MENU);
                
            }
            
        } else {
            game->state_mgr.change_state(GAME_STATE_LOADING);
            
        }
        
    } else if(
        sub_state >= SUB_STATE_CELEBRATING &&
        sub_state <= SUB_STATE_ANALYSIS_2 &&
        ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
    ) {
        analysis_darken_opacity = ANALYSIS_DARKEN_VALUE;
        sub_state = SUB_STATE_ANALYSIS_FULL;
    }
    
    if(
        sub_state == SUB_STATE_PICKING && ev.mouse.button == 2 &&
        ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
    ) {
        //DEBUG - Uncomment this to re-ink the chapter on RMB click.
        //TODO
        for(size_t x = 0; x < game->cur_chapter.width; ++x) {
            for(size_t y = 0; y < game->cur_chapter.height; ++y) {
                game->cur_chapter.grid[x][y].team = TEAM_NONE;
            }
        }
        for(size_t t = 0; t < 2; ++t) {
            for(size_t i = 0; i < N_INKLINGS; ++i) {
                game->cur_chapter.inklings[t][i].pos =
                    game->cur_chapter.spawns[t];
            }
        }
        game->cur_chapter.do_match();
        game->cur_chapter.calculate_real_percentages();
        game->cur_chapter.render();
        
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
    
    if(sub_state == SUB_STATE_STORY_WRITING) {
        if(cur_message_char < cur_message.size()) {
            cur_message_char_timer -= 1.0 / GAME_FPS;
            if(cur_message_char_timer < 0) {
                cur_message_char_timer = MESSAGE_CHAR_INTERVAL;
                cur_message_char++;
                if(cur_message_char == cur_message.size()) {
                    sub_state = SUB_STATE_STORY_WAITING;
                }
            }
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
    
    
    if(show_arena) {
        draw_textured_rectangle(
            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
            game->cur_chapter.background_bmp, al_map_rgb(255, 255, 255),
            0
        );
        al_draw_bitmap(
            game->cur_chapter.arena_bmp,
            WINDOW_WIDTH / 2.0 - game->cur_chapter.width / 2.0,
            4, 0
        );
        
    } else {
        al_draw_bitmap(game->bmp_title_background, 0, 0, 0);
        
    }
    
    if(show_ink) {
        al_draw_tinted_bitmap(
            game->cur_chapter.result_bmp, al_map_rgba(255, 255, 255, 210),
            WINDOW_WIDTH / 2.0 - game->cur_chapter.width / 2.0, 4, 0
        );
    }
    
    if(
        sub_state == SUB_STATE_STORY_WRITING ||
        sub_state == SUB_STATE_STORY_WAITING
    ) {
        al_draw_filled_rectangle(
            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
            al_map_rgba(0, 0, 0, 128)
        );
        
        ALLEGRO_COLOR text_color;
        int text_align;
        int text_x;
        if(dev_text) {
            text_color = al_map_rgb(160, 112, 255);
            text_align = ALLEGRO_ALIGN_CENTER;
            text_x = WINDOW_WIDTH * 0.5;
        } else {
            text_color = al_map_rgb(255, 255, 255);
            text_align = ALLEGRO_ALIGN_LEFT;
            text_x = STORY_X;
        }
        
        draw_shadowed_text(
            game->font, text_color,
            text_x, STORY_Y, text_align,
            cur_message.substr(0, cur_message_char + 1),
            STORY_SCALE, true
        );
        
        al_draw_bitmap(
            mouse_on_skip_button ?
            game->bmp_button_s_selected :
            game->bmp_button_s_unselected,
            SKIP_BUTTON_X, SKIP_BUTTON_Y, 0
        );
        
        draw_shadowed_text(
            game->font, al_map_rgb(192, 192, 192),
            STORY_CLICK_NOTE_X, STORY_CLICK_NOTE_Y,
            ALLEGRO_ALIGN_RIGHT, "Click anywhere to continue...",
            STORY_CLICK_NOTE_SCALE
        );
        
    }
    
    if(sub_state >= SUB_STATE_PICKING) {
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
        
        //DEBUG - Uncomment this to show the real percentages.
        /*
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255), 0, 8, 0,
            f2s(game->cur_chapter.real_percentages[TEAM_1]) + ";" +
            f2s(game->cur_chapter.real_percentages[TEAM_2]) + ";" +
            f2s(game->cur_chapter.real_percentages[TEAM_NONE]),
            0.5
        );
        */
        
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
                (chosen_team == TEAM_1 ? 1 : 0)
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
                (chosen_team == TEAM_2 ? 1 : 0)
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
                (chosen_team != TEAM_NONE ? 1 : 0)
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
                (chosen_team != TEAM_NONE ? 1 : 0)
            );
            
            draw_textured_rectangle(
                PICKER_I_UNINKED_X, PICKER_I_UNINKED_Y,
                PICKER_I_UNINKED_W, PICKER_I_UNINKED_H,
                game->bmp_checkerboard, al_map_rgb(255, 255, 255), 2
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
            draw_shadowed_text(
                game->font, al_map_rgb(255, 255, 255),
                PICKER_I_UNINKED_X + PICKER_I_UNINKED_W * 0.5,
                PICKER_I_UNINKED_Y + PICKER_I_UNINKED_H * 0.5,
                ALLEGRO_ALIGN_CENTER,
                "(" + f2s(game->cur_chapter.real_percentages[TEAM_NONE]) +
                "% uninked)",
                PICKER_I_UNINKED_SCALE
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
                (chosen_team != TEAM_NONE ? 1 : 0)
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
                (chosen_team != TEAM_NONE ? 1 : 0)
            );
            
            draw_textured_rectangle(
                PICKER_E_NONE_BAR_X, PICKER_E_NONE_BAR_Y,
                picker_unclaimed_x, PICKER_E_NONE_BAR_H,
                game->bmp_checkerboard, al_map_rgb(128, 128, 128), 2
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
        
    }
    
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
            "YOUR SCORE: " + i2s(player_score)
        );
        
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_COMMENT_X, ANALYSIS_COMMENT_Y,
            ALLEGRO_ALIGN_CENTER, "\"" + committee_comment + "\"",
            ANALYSIS_COMMENT_SCALE
        );
        draw_shadowed_text(
            game->font, al_map_rgb(255, 255, 255),
            ANALYSIS_COMMENT_SIGNED_X, ANALYSIS_COMMENT_SIGNED_Y,
            ALLEGRO_ALIGN_CENTER, "-- The committee",
            ANALYSIS_COMMENT_SIGNED_SCALE
        );
        
        ALLEGRO_BITMAP* b =
            player_score >= PASSING_SCORE ?
            game->bmp_stamp_pass :
            game->bmp_stamp_fail;
        al_draw_scaled_rotated_bitmap(
            b,
            al_get_bitmap_width(b) * 0.5, al_get_bitmap_height(b) * 0.5,
            ANALYSIS_STAMP_X, ANALYSIS_STAMP_Y,
            ANALYSIS_STAMP_SCALE, ANALYSIS_STAMP_SCALE,
            ANALYSIS_STAMP_ANGLE, 0
        );
        
        draw_shadowed_text(
            game->font, al_map_rgb(192, 192, 192),
            ANALYSIS_CLICK_NOTE_X, ANALYSIS_CLICK_NOTE_Y,
            ALLEGRO_ALIGN_RIGHT, "Click anywhere to continue...",
            ANALYSIS_CLICK_NOTE_SCALE
        );
        
    }
    
    al_flip_display();
}


void Gameplay::unload() {
    al_set_system_mouse_cursor(
        game->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT
    );
}


void Gameplay::draw_textured_rectangle(
    const int x, const int y, const int w, const int h,
    ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR color,
    const unsigned char movement_pattern
) {
    ALLEGRO_VERTEX vertexes[4];
    
    for(unsigned char v = 0; v < 4; ++v) {
        vertexes[v].z = 0;
        vertexes[v].color = color;
    }
    
    Point mov;
    if(movement_pattern == 1) {
        mov = Point(-(game->time_spent * 10), -(game->time_spent * 20));
    } else if(movement_pattern == 2) {
        mov = Point((game->time_spent * 20), 0);
    }
    
    vertexes[0].x = x;
    vertexes[0].y = y;
    vertexes[0].u = x + mov.x;
    vertexes[0].v = y + mov.y;
    
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
    //If the ink percentages would appear the same to the player,
    //skewer them in the player's favor, since there can be no ties.
    if(
        f2s(game->cur_chapter.real_percentages[TEAM_1]) ==
        f2s(game->cur_chapter.real_percentages[TEAM_2])
    ) {
        if(chosen_team == TEAM_1) {
            game->cur_chapter.real_percentages[TEAM_1] += 0.1;
            game->cur_chapter.real_percentages[TEAM_2] -= 0.1;
        } else {
            game->cur_chapter.real_percentages[TEAM_2] += 0.1;
            game->cur_chapter.real_percentages[TEAM_1] -= 0.1;
        }
        for(unsigned char t = 0; t < 2; ++t) {
            game->cur_chapter.real_percentages[t] =
                max(0.0f, game->cur_chapter.real_percentages[t]);
            game->cur_chapter.real_percentages[t] =
                min(game->cur_chapter.real_percentages[t], 100.0f);
        }
    }
    
    unsigned char real_winner =
        game->cur_chapter.real_percentages[TEAM_1] >
        game->cur_chapter.real_percentages[TEAM_2] ? TEAM_1 : TEAM_2;
        
    if(real_winner != chosen_team) {
        player_score = 0;
        
        if(game->chapter_to_load == 1) {
            //Different message for the first chapter.
            committee_comment =
                "Drat! That was the wrong choice, Judd! Perhaps\n"
                "you weren't cut out for this job after all... Sorry.";
                
        } else {
            string c1 =
                rp("Shoot", "Oh no") + "! We can't let the " +
                rp("wrong", "losing") + " team " +
                rp("be the winners", "win") +
                "!\n" + rp("Sorry", "I'm sorry") +
                ", but we'll have to fire you.";
            string c2 =
                "We can't just let the " + rp("loser", "losing") + " team get "
                + rp("away with the", "the") + " " +
                rp("reward", "prize") + "!\n" + rp("I'm sorry", "Sorry") +
                ", but you're fired.";
            string c3 =
                "Your guess " + rp("was wrong", "wasn't right") + ", and now"
                " the " + rp("winning", "winner") + " team\nleft " +
                rp("with empty hands", "empty-handed") +
                "! We'll have to lay you off.";
                
            committee_comment = rp(c1, c2, c3);
            
        }
        
        return;
    }
    
    if(difficulty == DIFFICULTY_BEGINNER) {
        player_score = 100;
        
        if(game->chapter_to_load == 1) {
            //Different message for the first chapter.
            committee_comment =
                "Good work, Judd. Your first day was a success!\n"
                "We knew you would be perfect for the task.";
                
        } else {
            string c1 =
                rp("Nice", "Great", "Terrific", "Wonderful") + " work, " +
                rp("ace", "Judd") + "! We're glad we can count\non " +
                rp("you", "your efforts") + ". Keep " +
                rp("it up", "up the good work") + rp(".", "!");
            string c2 =
                rp("And another", "Yet another", "Another") + " " +
                rp("fine", "great") + " guess, Judd!\nWe're happy we " +
                rp("chose", "picked") + " you for the " + rp("job", "task") +
                ".";
            committee_comment = rp(c1, c2);
            
        }
        
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
    player_score = round(player_score);
    
    if(player_score == 0) {
        committee_comment =
            rp("Judd", "Wow", "Uhm") + "... " +
            rp("Don't tell me", "Let me guess") + ", you purposely tried to"
            " get\nthe worst " + rp("possible score", "score possible") +
            ", " + rp("right", "am I right", "correct", "is that it") + "?";
            
    } else if(player_score > 0 && player_score < 25) {
        string c1 =
            rp("Why", "Judd") + ", this is a " + rp("terrible", "horrible") +
            " guess!\nWhat " +
            rp("has gotten into you?", "is wrong with you?") +
            " We'll have to lay you off.";
        string c2 =
            "You were " + rp("very", "quite") + " far off! Your guess is " +
            rp("of no use", "useless") + "!\nSorry, but you're " +
            rp("hereby", "officially") + " fired!";
        committee_comment = rp(c1, c2);
        
    } else if(player_score >= 25 && player_score < 50) {
        committee_comment =
            "Your " + rp("guess", "decision") + " won't do, since it's too " +
            rp("far off", "inaccurate") + "!\nWe can't " +
            rp("just let", "let") + " you " + rp("continue", "go on") +
            " after this " + rp("mistake", "blunder") + ".";
            
    } else if(player_score >= 50 && player_score < 75) {
        committee_comment =
            "You weren't " + rp("close", "accurate") + " enough... We expected"
            " a more\naccurate " + rp("guess", "result") + ". Sorry, but we'll"
            " have to " + rp("lay you off", "let you go") + ".";
            
    } else if(player_score >= 75 && player_score < PASSING_SCORE) {
        string c1 =
            "Your " + rp("decision", "guess") + " was good, but we " +
            rp("require", "need") + " more accuracy. We'll\n"
            "lay you off for a " + rp("bit", "while") + " so you can get " +
            rp("that", "your") + " spark back, okay?";
        string c2 =
            "Your " + rp("answer", "choice") + " wasn't good enough,"
            " I'm afraid. We'll\ndismiss you for a " + rp("while", "bit") +
            " so you can clear your mind, okay?";
        committee_comment = rp(c1, c2);
        
    } else if(player_score >= PASSING_SCORE && player_score <= 99.9) {
        string c1 =
            "Congrats on " + rp("yet another", "another") + " good " +
            rp("guess", "call") + ", Judd!\nWe're glad to have you " +
            rp("on board", "on the job") + ".";
        string c2 =
            rp("Well", "Nicely") + " done! Your guesses save the day once " +
            rp("more", "again") + ".\nKeep up the good work, " +
            rp("ace", "champ") + "!";
        string c3 =
            "Another " + rp("great", "good", "fine") + " guess. We knew"
            " we could count\non " + rp("you", "your efforts") + "."
            " Don't let us down!";
        committee_comment = rp(c1, c2, c3);
        
    } else {
        string c1 =
            "Why, this is " + rp("astonishing", "incredible", "amazing") + "!"
            " You were completely " + rp("right", "spot-on") + "\n"
            "about your guess! " + rp("Thank you", "Many thanks") +
            " for your continued efforts!";
        string c2 =
            rp("Incredible", "Terrific", "Amazing") + "! You were " +
            rp("spot-on", "right on the mark") + "!\nWe " +
            rp("can't", "just can't") + " thank you enough for what you do.";
        string c3 =
            "You actually guessed perfectly! " +
            rp("Outstanding", "Amazing", "Spectacular") + " work " +
            rp("out there, ace", ", ace") + "!\nWe're happy we can use your " +
            rp("wonderful", "incredible") + " skills.";
        committee_comment = rp(c1, c2, c3);
        
    }
}


void Gameplay::advance_story() {
    if(
        cur_message_block <
        game->cur_chapter.chapter_data->story.size() - 1
    ) {
        cur_message_block++;
        cur_message =
            game->cur_chapter.chapter_data->story[cur_message_block];
        cur_message_char = 0;
        cur_message_char_timer = MESSAGE_CHAR_INTERVAL;
        sub_state = SUB_STATE_STORY_WRITING;
        
        if(cur_message == "#arena") {
            show_arena = true;
            advance_story();
        } else if(cur_message == "#ink") {
            show_ink = true;
            advance_story();
        } else if(cur_message == "#devtext") {
            dev_text = true;
            advance_story();
        }
        
    } else {
        sub_state = SUB_STATE_PICKING;
        show_arena = true;
        show_ink = true;
    }
}


float Gameplay::ease_hop(const float n) {
    //From http://i.stack.imgur.com/vqA2E.jpg
    return n * (n * (4 * n - 9) + 6);
}


bool Gameplay::Confetto::tick() {
    pos += speed * (1.0 / GAME_FPS);
    angle += rotation_speed * 1.0 / GAME_FPS;
    if(pos.y > WINDOW_HEIGHT + CONFETTO_W * 2) {
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
            -(CONFETTO_W * 0.5), -(CONFETTO_H * 0.5),
            (CONFETTO_W * 0.5), (CONFETTO_H * 0.5),
            color
        );
    } al_use_transform(&old_transform);
}
