#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "chapter_data.h"
#include "const.h"
#include "game.h"
#include "gameplay.h"
#include "loading.h"
#include "main_menu.h"
#include "utils.h"


Game::Game() :
    running(true),
    display(nullptr),
    queue(nullptr),
    timer(nullptr),
    state_mgr(),
    chapter_to_load(0),
    free_play_difficulty(DIFFICULTY_BEGINNER) {
    
    srand(time(NULL));
    
    al_init();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    timer = al_create_timer(1.0 / GAME_FPS);
    queue = al_create_event_queue();
    
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    
    al_set_window_title(display, GAME_TITLE.c_str());
    
    al_set_new_bitmap_flags(
        ALLEGRO_MIN_LINEAR | ALLEGRO_MIN_LINEAR
    );
    
    font =
        al_load_ttf_font(
            (GRAPHICS_FOLDER + "/" + FONT_FILE_NAME).c_str(),
            FONT_SIZE, 0
        );
    big_font =
        al_load_ttf_font(
            (GRAPHICS_FOLDER + "/" + FONT_FILE_NAME).c_str(),
            FONT_SIZE * 2.0, 0
        );
        
    bmp_button_r_unselected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_R_UNSELECTED).c_str());
    bmp_button_r_selected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_R_SELECTED).c_str());
    bmp_button_l_unselected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_L_UNSELECTED).c_str());
    bmp_button_l_selected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_L_SELECTED).c_str());
    bmp_button_k_unselected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_K_UNSELECTED).c_str());
    bmp_button_k_selected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_K_SELECTED).c_str());
    bmp_button_s_unselected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_S_UNSELECTED).c_str());
    bmp_button_s_selected = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BUTTON_S_SELECTED).c_str());
    bmp_picker_b = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_PICKER_B).c_str());
    bmp_picker_i = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_PICKER_I).c_str());
    bmp_picker_e = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_PICKER_E).c_str());
    bmp_ink_effect = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_INK_EFFECT).c_str());
    bmp_checkerboard = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_CHECKERBOARD).c_str());
    bmp_splash = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_SPLASH).c_str());
    bmp_logo = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_LOGO).c_str());
    bmp_title_background = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_TITLE_BG).c_str());
    bmp_judd_r = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_JUDD_R).c_str());
    bmp_judd_l = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_JUDD_L).c_str());
    bmp_flag_r = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_FLAG_R).c_str());
    bmp_flag_l = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_FLAG_L).c_str());
    bmp_stamp_fail = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_STAMP_FAIL).c_str());
    bmp_stamp_pass = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_STAMP_PASS).c_str());
    bmp_difficulty_icon[0] = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_BEGINNER_ICON).c_str());
    bmp_difficulty_icon[1] = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_INTERMEDIATE_ICON).c_str());
    bmp_difficulty_icon[2] = al_load_bitmap((GRAPHICS_FOLDER + "/" + BMP_EXPERT_ICON).c_str());
    
    for(size_t a = 0; a < N_ARENAS; ++a) {
        bmp_arena_data[a] =
            load_png_or_jpg(GRAPHICS_FOLDER + "/arenas/" + i2s(a) + "_data");
        bmp_arena[a] =
            load_png_or_jpg(GRAPHICS_FOLDER + "/arenas/" + i2s(a));
        bmp_arena_bg[a] =
            load_png_or_jpg(GRAPHICS_FOLDER + "/arenas/" + i2s(a) + "_bg");
    }
    
    all_chapter_data = get_chapters();
    
    for(size_t c = 0; c < all_chapter_data.size(); ++c) {
        high_scores.push_back(0);
    }
    
    load_save_data();
    
#define register_color(r1, g1, b1, r2, g2, b2) \
    all_ink_colors.push_back( \
                              make_pair( \
                                         al_map_rgb(r1, g1, b1), \
                                         al_map_rgb(r2, g2, b2) \
                                       ) \
                            )
    
    register_color(200, 61,  121, 64,  157, 59);
    register_color(201, 52,  87,  4,   129, 136);
    register_color(218, 55,  129, 237, 148, 8);
    register_color(207, 88,  27,  20,  20,  148);
    register_color(121, 149, 22,  110, 6,   138);
    register_color(32,  131, 125, 223, 100, 26);
    register_color(34,  140, 255, 232, 84,  7);
    register_color(0,   126, 220, 225, 163, 7);
    register_color(46,  12,  181, 248, 99,  0);
    register_color(38,  34,  159, 145, 176, 11);
    
#undef register_color
    
    state_mgr.register_state(GAME_STATE_MAIN_MENU, new Main_Menu(this));
    state_mgr.register_state(GAME_STATE_LOADING, new Loading(this));
    state_mgr.register_state(GAME_STATE_GAMEPLAY, new Gameplay(this));
    state_mgr.change_state(GAME_STATE_MAIN_MENU);
    
    al_start_timer(timer);
}


void Game::loop() {
    al_start_timer(timer);
    
    while(running) {
        al_wait_for_event(queue, &ev);
        
        Game_State* cur_state = state_mgr.get_current_state();
        
        if(ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            time_spent += 1.0 / GAME_FPS;
            cur_state->do_drawing();
            cur_state->do_logic();
            
        } else if(
            ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
            ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
            ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP
        ) {
            cur_state->handle_mouse(ev);
            
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            
        }
    }
}


void Game::draw_judd(
    const float pivot_x, const float pivot_y, const float scale,
    const bool right, const ALLEGRO_COLOR flag_color
) {
    ALLEGRO_BITMAP* judd_bmp =
        right ? bmp_judd_r : bmp_judd_l;
    ALLEGRO_BITMAP* flag_bmp =
        right ? bmp_flag_r : bmp_flag_l;
    int flag_x =
        right ? 451 : -70;
    int flag_y =
        right ? 95 : 90;
    int feet_x =
        right ? 188 : 437;
        
    int judd_bmp_w = al_get_bitmap_width(judd_bmp);
    int judd_bmp_h = al_get_bitmap_height(judd_bmp);
    int flag_bmp_w = al_get_bitmap_width(flag_bmp);
    int flag_bmp_h = al_get_bitmap_height(flag_bmp);
    int judd_x = pivot_x - (feet_x * scale);
    int judd_y = pivot_y - (judd_bmp_h * scale);
    al_draw_tinted_scaled_bitmap(
        flag_bmp, flag_color,
        0, 0, flag_bmp_w, flag_bmp_h,
        judd_x + (flag_x * scale), judd_y + (flag_y * scale),
        flag_bmp_w * scale, flag_bmp_h * scale,
        0
    );
    al_draw_scaled_bitmap(
        judd_bmp,
        0, 0, judd_bmp_w, judd_bmp_h,
        judd_x, judd_y, judd_bmp_w * scale, judd_bmp_h * scale,
        0
    );
}


void Game::load_save_data() {
    ALLEGRO_FILE* file = al_fopen(SAVE_FILE_NAME.c_str(), "rb");
    if(!file) return;
    
    unsigned char* new_high_scores = new unsigned char[all_chapter_data.size()];
    
    size_t n_read = al_fread(file, new_high_scores, all_chapter_data.size());
    
    if(n_read == all_chapter_data.size()) {
        for(size_t c = 0; c < all_chapter_data.size(); ++c) {
            high_scores[c] = new_high_scores[c];
        }
    }
    
    delete[] new_high_scores;
    al_fclose(file);
}


void Game::save_save_data() {
    ALLEGRO_FILE* file = al_fopen(SAVE_FILE_NAME.c_str(), "wb");
    if(!file) return;
    
    for(size_t c = 0; c < all_chapter_data.size(); ++c) {
        unsigned char byte = high_scores[c];
        al_fwrite(file, &byte, 1);
    }
    
    al_fclose(file);
}
