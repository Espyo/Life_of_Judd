#include <math.h>

#include "const.h"
#include "game.h"
#include "main_menu.h"
#include "utils.h"


/* ----------------------------------------------------------------------------
 * Constructs a main menu game state.
 */
Main_Menu::Main_Menu(Game* game) :
    Game_State(game),
    mouse_on_story_start_button(false),
    mouse_on_next_chapter_button(false),
    mouse_on_prev_chapter_button(false),
    mouse_on_free_play_start_button(false),
    mouse_on_next_difficulty_button(false),
    mouse_on_prev_difficulty_button(false),
    last_open_chapter(1),
    chosen_chapter(1),
    logo_split_x(0.5) {
    
    
}


/* ----------------------------------------------------------------------------
 * Destroys a main menu game state.
 */
Main_Menu::~Main_Menu() {
}


/* ----------------------------------------------------------------------------
 * Code to run when going to the main menu.
 */
void Main_Menu::load() {
    logo_split_x = al_get_bitmap_width(game->bmp_logo) * randomf(0.1, 0.9);
    
    size_t ink_pair = randomi(0, game->all_ink_colors.size() - 1);
    ink_colors[0] = game->all_ink_colors[ink_pair].first;
    ink_colors[1] = game->all_ink_colors[ink_pair].second;
    
    mouse_on_story_start_button = false;
    mouse_on_next_chapter_button = false;
    mouse_on_prev_chapter_button = false;
    mouse_on_free_play_start_button = false;
    mouse_on_next_difficulty_button = false;
    mouse_on_prev_difficulty_button = false;
    
    last_open_chapter = 1;
    for(size_t c = 0; c < game->all_chapter_data.size(); ++c) {
        if(game->high_scores[c] >= PASSING_SCORE) {
            last_open_chapter = c + 1;
        } else {
            last_open_chapter = c + 1;
            break;
        }
    }
    
    if(game->chapter_to_load > 0) chosen_chapter = game->chapter_to_load;
    
    //DEBUG - Uncomment this to automatically pick the last available chapter.
    //chosen_chapter = last_open_chapter;
}


/* ----------------------------------------------------------------------------
 * Code to run when leaving the main menu.
 */
void Main_Menu::unload() {
    al_set_system_mouse_cursor(
        game->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT
    );
}


/* ----------------------------------------------------------------------------
 * Code to run when handling a mouse event on the main menu.
 */
void Main_Menu::handle_mouse(ALLEGRO_EVENT ev) {
    ALLEGRO_SYSTEM_MOUSE_CURSOR cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
    
    if(
        ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
        ev.type == ALLEGRO_EVENT_MOUSE_AXES
    ) {
        mouse_on_story_start_button =
            ev.mouse.x >= MAIN_MENU_STORY_X &&
            ev.mouse.x <= MAIN_MENU_STORY_X + MAIN_MENU_STORY_W &&
            ev.mouse.y >= MAIN_MENU_STORY_Y - MAIN_MENU_STORY_H * 0.5 &&
            ev.mouse.y <= MAIN_MENU_STORY_Y + MAIN_MENU_STORY_H * 0.5;
        mouse_on_prev_chapter_button =
            ev.mouse.x >= PREV_BUTTON_X &&
            ev.mouse.x <= PREV_BUTTON_X + PREV_BUTTON_W &&
            ev.mouse.y >= CHAPTER_BUTTON_Y &&
            ev.mouse.y <= CHAPTER_BUTTON_Y + PREV_BUTTON_H;
        mouse_on_next_chapter_button =
            ev.mouse.x >= NEXT_BUTTON_X &&
            ev.mouse.x <= NEXT_BUTTON_X + NEXT_BUTTON_W &&
            ev.mouse.y >= CHAPTER_BUTTON_Y &&
            ev.mouse.y <= CHAPTER_BUTTON_Y + NEXT_BUTTON_H;
            
        mouse_on_free_play_start_button =
            ev.mouse.x >= FREE_X &&
            ev.mouse.x <= FREE_X + FREE_W &&
            ev.mouse.y >= FREE_Y - FREE_H * 0.5 &&
            ev.mouse.y <= FREE_Y + FREE_H * 0.5;
        mouse_on_prev_difficulty_button =
            ev.mouse.x >= PREV_BUTTON_X &&
            ev.mouse.x <= PREV_BUTTON_X + PREV_BUTTON_W &&
            ev.mouse.y >= FREE_BUTTON_Y &&
            ev.mouse.y <= FREE_BUTTON_Y + PREV_BUTTON_H;
        mouse_on_next_difficulty_button =
            ev.mouse.x >= NEXT_BUTTON_X &&
            ev.mouse.x <= NEXT_BUTTON_X + NEXT_BUTTON_W &&
            ev.mouse.y >= FREE_BUTTON_Y &&
            ev.mouse.y <= FREE_BUTTON_Y + NEXT_BUTTON_H;
    }
    
    if(
        mouse_on_prev_chapter_button || mouse_on_next_chapter_button ||
        mouse_on_prev_difficulty_button || mouse_on_next_difficulty_button ||
        mouse_on_story_start_button || mouse_on_free_play_start_button
    ) {
        cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK;
    }
    
    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(mouse_on_prev_chapter_button) {
            if(chosen_chapter == 1) {
                chosen_chapter = last_open_chapter;
            } else {
                chosen_chapter--;
            }
            
        } else if(mouse_on_next_chapter_button) {
            if(chosen_chapter == last_open_chapter) {
                chosen_chapter = 1;
            } else {
                chosen_chapter++;
            }
            
        } else if(mouse_on_prev_difficulty_button) {
            if(game->free_play_difficulty == 0) {
                game->free_play_difficulty = 2;
            } else {
                game->free_play_difficulty--;
            }
            
        } else if(mouse_on_next_difficulty_button) {
            if(game->free_play_difficulty == 2) {
                game->free_play_difficulty = 0;
            } else {
                game->free_play_difficulty++;
            }
            
        } else if(mouse_on_story_start_button) {
            game->chapter_to_load = chosen_chapter;
            game->state_mgr.change_state(GAME_STATE_LOADING);
            
        } else if(mouse_on_free_play_start_button) {
            game->chapter_to_load = 0;
            game->state_mgr.change_state(GAME_STATE_LOADING);
            
        }
    }
    
    al_set_system_mouse_cursor(game->display, cursor);
    
}


/* ----------------------------------------------------------------------------
 * Code to run each timer tick on the main menu.
 */
void Main_Menu::do_logic() {

}


/* ----------------------------------------------------------------------------
 * Code to run when drawing the screen on the main menu.
 */
void Main_Menu::do_drawing() {
    al_clear_to_color(al_map_rgb(0, 128, 0));
    
    al_draw_bitmap(game->bmp_title_background, 0, 0, 0);
    
    unsigned char winner =
        (logo_split_x > al_get_bitmap_width(game->bmp_logo) * 0.5) ?
        TEAM_1 : TEAM_2;
        
    game->draw_judd(
        JUDD_PIVOT_X, JUDD_PIVOT_Y, MAIN_MENU_JUDD_SCALE,
        winner == TEAM_2, ink_colors[winner]
    );
    
    int logo_width = al_get_bitmap_width(game->bmp_logo);
    int logo_height = al_get_bitmap_height(game->bmp_logo);
    
    for(unsigned char i = 0; i < 2; ++i) {
        al_draw_tinted_scaled_bitmap(
            game->bmp_logo,
            darken_color(ink_colors[TEAM_1], (i == 0 ? 0.3 : 1.0)),
            0, 0, logo_split_x, logo_height,
            (LOGO_X - logo_width * 0.5) + (i == 0 ? 4 : 0),
            (LOGO_Y - logo_height * 0.5) + (i == 0 ? 4 : 0),
            logo_split_x,
            logo_height, 0
        );
        al_draw_tinted_scaled_bitmap(
            game->bmp_logo,
            darken_color(ink_colors[TEAM_2], (i == 0 ? 0.3 : 1.0)),
            logo_split_x, 0,
            logo_width - logo_split_x, logo_height,
            (LOGO_X - logo_width * 0.5) + logo_split_x + (i == 0 ? 4 : 0),
            (LOGO_Y - logo_height * 0.5) + (i == 0 ? 4 : 0),
            logo_width - logo_split_x,
            logo_height, 0
        );
    }
    
    if(mouse_on_story_start_button) {
        al_draw_tinted_bitmap(
            game->bmp_splash, ink_colors[winner],
            (MAIN_MENU_STORY_X + MAIN_MENU_STORY_W * 0.5) -
            (al_get_bitmap_width(game->bmp_splash) * 0.5),
            MAIN_MENU_STORY_Y -
            (al_get_bitmap_height(game->bmp_splash) * 0.5),
            0
        );
    }
    
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        MAIN_MENU_STORY_X, MAIN_MENU_STORY_Y, 0, "STORY MODE"
    );
    
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        CHAPTER_NAME_X, CHAPTER_NAME_Y, 0,
        game->all_chapter_data[chosen_chapter - 1].name,
        0.5
    );
    
    ALLEGRO_COLOR high_score_color;
    if(game->high_scores[chosen_chapter - 1] < PASSING_SCORE) {
        high_score_color = al_map_rgb(255, 192, 192);
    } else if(game->high_scores[chosen_chapter - 1] < 100) {
        high_score_color = al_map_rgb(192, 192, 255);
    } else {
        high_score_color = al_map_rgb(192, 255, 192);
    }
    
    draw_shadowed_text(
        game->font, high_score_color,
        CHAPTER_SCORE_X, CHAPTER_SCORE_Y, 0,
        "High score: " + i2s(game->high_scores[chosen_chapter - 1]),
        0.5
    );
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        CHAPTER_DIFFICULTY_X, CHAPTER_DIFFICULTY_Y, 0, "Difficulty:", 0.5
    );
    ALLEGRO_BITMAP* b =
        game->bmp_difficulty_icon[
            game->all_chapter_data[chosen_chapter - 1].difficulty
        ];
    al_draw_bitmap(
        b,
        CHAPTER_DIFFICULTY_ICON_X - al_get_bitmap_width(b) * 0.5,
        CHAPTER_DIFFICULTY_Y - al_get_bitmap_height(b) * 0.5,
        0
    );
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        CHAPTER_DIFFICULTY_NAME_X, CHAPTER_DIFFICULTY_Y, ALLEGRO_ALIGN_LEFT,
        get_difficulty_name(
            game->all_chapter_data[chosen_chapter - 1].difficulty
        ),
        DIFFICULTY_NAME_SCALE
    );
    
    b =
        mouse_on_prev_chapter_button ? game->bmp_button_l_selected :
        game->bmp_button_l_unselected;
    al_draw_scaled_bitmap(
        b, 0, 0,
        al_get_bitmap_width(b), al_get_bitmap_height(b),
        PREV_BUTTON_X, CHAPTER_BUTTON_Y,
        PREV_BUTTON_W, PREV_BUTTON_H,
        0
    );
    b =
        mouse_on_next_chapter_button ? game->bmp_button_r_selected :
        game->bmp_button_r_unselected;
    al_draw_scaled_bitmap(
        b, 0, 0,
        al_get_bitmap_width(b), al_get_bitmap_height(b),
        NEXT_BUTTON_X, CHAPTER_BUTTON_Y,
        NEXT_BUTTON_W, NEXT_BUTTON_H,
        0
    );
    
    if(mouse_on_free_play_start_button) {
        al_draw_tinted_bitmap(
            game->bmp_splash, ink_colors[winner],
            (FREE_X + FREE_W * 0.5) -
            (al_get_bitmap_width(game->bmp_splash) * 0.5),
            FREE_Y -
            (al_get_bitmap_height(game->bmp_splash) * 0.5),
            0
        );
    }
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        FREE_X, FREE_Y, 0, "FREE PLAY MODE"
    );
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        FREE_DIFFICULTY_X, FREE_DIFFICULTY_Y, 0, "Difficulty:", 0.5
    );
    b = game->bmp_difficulty_icon[game->free_play_difficulty];
    al_draw_bitmap(
        b,
        FREE_DIFFICULTY_ICON_X - al_get_bitmap_width(b) * 0.5,
        FREE_DIFFICULTY_Y - al_get_bitmap_height(b) * 0.5,
        0
    );
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        FREE_DIFFICULTY_NAME_X, FREE_DIFFICULTY_Y, ALLEGRO_ALIGN_LEFT,
        get_difficulty_name(game->free_play_difficulty),
        DIFFICULTY_NAME_SCALE
    );
    
    b =
        mouse_on_prev_difficulty_button ? game->bmp_button_l_selected :
        game->bmp_button_l_unselected;
    al_draw_scaled_bitmap(
        b, 0, 0,
        al_get_bitmap_width(b), al_get_bitmap_height(b),
        PREV_BUTTON_X, FREE_BUTTON_Y,
        PREV_BUTTON_W, PREV_BUTTON_H,
        0
    );
    b =
        mouse_on_next_difficulty_button ? game->bmp_button_r_selected :
        game->bmp_button_r_unselected;
    al_draw_scaled_bitmap(
        b, 0, 0,
        al_get_bitmap_width(b), al_get_bitmap_height(b),
        NEXT_BUTTON_X, FREE_BUTTON_Y,
        NEXT_BUTTON_W, NEXT_BUTTON_H,
        0
    );
    
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        DISCLAIMER_X, DISCLAIMER_Y, ALLEGRO_ALIGN_CENTER,
        DISCLAIMER_TEXT, DISCLAIMER_SCALE
    );
    
    if(game->cant_save && (int) (floor(game->time_spent * 2)) % 2 == 0) {
        draw_shadowed_text(
            game->font, al_map_rgb(255, 192, 192),
            SAVE_WARNING_X, SAVE_WARNING_Y, ALLEGRO_ALIGN_CENTER,
            SAVE_WARNING_TEXT, SAVE_WARNING_SCALE
        );
    }
    
    
    al_flip_display();
}


/* ----------------------------------------------------------------------------
 * Returns the English name of a difficulty, given its ID.
 */
string Main_Menu::get_difficulty_name(const int difficulty_number) {
    if(difficulty_number == DIFFICULTY_BEGINNER) {
        return "Beginner";
    } else if(difficulty_number == DIFFICULTY_INTERMEDIATE) {
        return "Intermediate";
    } else {
        return "Expert";
    }
}
