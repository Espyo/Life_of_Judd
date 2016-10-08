#include "game.h"
#include "loading.h"
#include "utils.h"


/* ----------------------------------------------------------------------------
 * Constructs a loading screen game state.
 */
Loading::Loading(Game* game) :
    Game_State(game) {
    
    
}


/* ----------------------------------------------------------------------------
 * Destroys a loading screen game state.
 */
Loading::~Loading() {
}


/* ----------------------------------------------------------------------------
 * Code to run when entering the loading screen.
 */
void Loading::load() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_tinted_bitmap(
        game->bmp_title_background, al_map_rgb(96, 96, 96),
        0, 0, 0
    );
    draw_shadowed_text(
        game->font, al_map_rgb(255, 255, 255),
        WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5,
        ALLEGRO_ALIGN_CENTER, "LOADING..."
    );
    al_flip_display();
    
    if(game->chapter_to_load == 0) {
        game->random_chapter_data = generate_random_chapter_data(game);
        game->cur_chapter.chapter_data = &game->random_chapter_data;
    } else {
        game->cur_chapter.chapter_data =
            &game->all_chapter_data[game->chapter_to_load - 1];
    }
    
    ALLEGRO_BITMAP* data_bmp =
        game->bmp_arena_data[game->cur_chapter.chapter_data->arena_nr];
    ALLEGRO_BITMAP* arena_bmp =
        game->bmp_arena[game->cur_chapter.chapter_data->arena_nr];
    ALLEGRO_BITMAP* background_bmp =
        game->bmp_arena_bg[game->cur_chapter.chapter_data->arena_nr];
        
    game->cur_chapter.load(arena_bmp, data_bmp, background_bmp);
    game->cur_chapter.do_match();
    game->cur_chapter.calculate_real_percentages();
    game->cur_chapter.render();
    
    al_flush_event_queue(game->queue);
    
    game->state_mgr.change_state(GAME_STATE_GAMEPLAY);
}


/* ----------------------------------------------------------------------------
 * Code to run when leaving the loading screen.
 */
void Loading::unload() {

}


/* ----------------------------------------------------------------------------
 * Code to run to handle mouse events on the loading screen.
 */
void Loading::handle_mouse(ALLEGRO_EVENT ev) {

}


/* ----------------------------------------------------------------------------
 * Code to run on each timer tick on the loading screen.
 */
void Loading::do_logic() {

}


/* ----------------------------------------------------------------------------
 * Code to run when drawing the loading screen each frame.
 */
void Loading::do_drawing() {

}
