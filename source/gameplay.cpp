#include "game.h"
#include "gameplay.h"
#include "utils.h"


Gameplay::Gameplay(Game* game) :
    Game_State(game),
    game_mode(GAME_MODE_BEGINNER),
    mouse_on_ok_button(false),
    chosen_team(2) ,
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
                ev.mouse.y >= PICKER_1_TEAM_BUTTON_Y &&
                ev.mouse.y <= PICKER_1_TEAM_BUTTON_Y + PICKER_1_TEAM_BUTTON_H
            ) {
                if(
                    ev.mouse.x >= PICKER_1_TEAM_1_BUTTON_X &&
                    ev.mouse.x <= PICKER_1_TEAM_1_BUTTON_X +
                    PICKER_1_TEAM_BUTTON_W
                ) {
                    chosen_team = 0;
                    
                } else if(
                    ev.mouse.x >= PICKER_1_TEAM_2_BUTTON_X &&
                    ev.mouse.x <= PICKER_1_TEAM_2_BUTTON_X +
                    PICKER_1_TEAM_BUTTON_W
                ) {
                    chosen_team = 1;
                    
                }
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
    
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 0, 0, f2s(cur_arena.real_percentages[0]).c_str());
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 8, 0, f2s(cur_arena.real_percentages[1]).c_str());
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 0, 16, 0, f2s(cur_arena.real_percentages[2]).c_str());
    
    if(game_mode == GAME_MODE_BEGINNER) {
        draw_ink_button(
            PICKER_1_TEAM_1_BUTTON_X, PICKER_1_TEAM_BUTTON_Y,
            PICKER_1_TEAM_BUTTON_W, PICKER_1_TEAM_BUTTON_H,
            (
                chosen_team == 0 ?
                cur_arena.ink_colors[0] :
                darken_color(cur_arena.ink_colors[0], 0.5)
            ),
            (chosen_team == 0)
        );
        
        draw_ink_button(
            PICKER_1_TEAM_2_BUTTON_X, PICKER_1_TEAM_BUTTON_Y,
            PICKER_1_TEAM_BUTTON_W, PICKER_1_TEAM_BUTTON_H,
            (
                chosen_team == 1 ?
                cur_arena.ink_colors[1] :
                darken_color(cur_arena.ink_colors[1], 0.5)
            ),
            (chosen_team == 1)
        );
        
        al_draw_bitmap(bmp_picker_1, PICKER_1_X, PICKER_1_Y, 0);
        
        ALLEGRO_COLOR ok_button_tint = al_map_rgb(255, 255, 255);
        if(chosen_team != 2) {
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
    vertexes[0].u = (moving ? -(game->time_spent * 10) : 0);
    vertexes[0].v = (moving ? -(game->time_spent * 20) : 0);
    
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
