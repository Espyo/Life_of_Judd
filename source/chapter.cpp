#include <algorithm>

#include <allegro5/allegro_primitives.h> //Used for debugging

#include "chapter.h"
#include "chapter_data.h"
#include "utils.h"


/* ----------------------------------------------------------------------------
 * Constructs a chapter.
 */
Chapter::Chapter() :
    chapter_data(nullptr),
    width(0),
    height(0),
    spawn_dist(0),
    arena_bmp(nullptr),
    background_bmp(nullptr),
    result_bmp(nullptr)  {
    
    
}


/* ----------------------------------------------------------------------------
 * Loads a chapter into memory.
 */
void Chapter::load(
    ALLEGRO_BITMAP* arena_bmp, ALLEGRO_BITMAP* data_bmp, ALLEGRO_BITMAP* bg_bmp
) {
    this->arena_bmp = arena_bmp;
    this->background_bmp = bg_bmp;
    
    get_data_from_bmp(data_bmp);
    
    generate_data();
    
    {
        float dx = spawns[0].x - spawns[1].x;
        float dy = spawns[0].y - spawns[1].y;
        spawn_dist = sqrt(dx * dx + dy * dy);
    }
    result_bmp = al_create_bitmap(width, height);
    
}


/* ----------------------------------------------------------------------------
 * Generates some data for the chapter to work with, based on the
 * chapter data database.
 */
void Chapter::generate_data() {
    ink_colors[0] = chapter_data->ink_colors[0];
    ink_colors[1] = chapter_data->ink_colors[1];
    if(chapter_data->can_switch_teams && randomi(0, 100) < 50) {
        swap(ink_colors[0], ink_colors[1]);
    }
    
    bool do_swap = chapter_data->can_switch_teams && randomi(0, 100) < 50;
    
    for(size_t t = 0; t < 2; ++t) {
        size_t fetch_t = do_swap ? (t == 0 ? 1 : 0) : t;
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            inklings[t][i] = chapter_data->inklings[fetch_t][i];
            inklings[t][i].chapter = this;
            inklings[t][i].team = t;
            inklings[t][i].pos = spawns[t];
        }
        blotch_generators[t] = chapter_data->blotch_generators[fetch_t];
        blotch_generators[t].team = t;
    }
    
    blotch_generators[TEAM_NONE] = chapter_data->blotch_generators[TEAM_NONE];
}


/* ----------------------------------------------------------------------------
 * Gets some grid and spawn info from the data image of the arena.
 */
void Chapter::get_data_from_bmp(ALLEGRO_BITMAP* data_bmp) {
    width = al_get_bitmap_width(data_bmp);
    height = al_get_bitmap_height(data_bmp);
    
    grid.clear();
    
    for(size_t x = 0; x < width; ++x) {
        grid.push_back(vector<Cell>());
        vector<Cell>* row_ptr = &grid.back();
        
        for(size_t y = 0; y < height; ++y) {
            row_ptr->push_back(Cell());
        }
    }
    
    al_lock_bitmap(
        data_bmp, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_READONLY
    ); {
    
        ALLEGRO_COLOR gray = al_map_rgb(128, 128, 128);
        
        for(size_t x = 0; x < width; ++x) {
            for(size_t y = 0; y < height; ++y) {
                ALLEGRO_COLOR c = al_get_pixel(data_bmp, x, y);
                
                if(
                    c.r == 0 && c.g == 0 && c.b == 0
                ) {
                    grid[x][y].type = CELL_TYPE_VOID;
                    
                } else if(
                    c.r == gray.r && c.g == gray.r && c.b == gray.r
                ) {
                    grid[x][y].type = CELL_TYPE_UNINKABLE;
                    
                } else if(
                    c.r == 1 && c.g == 0 && c.b == 0
                ) {
                    spawns[0] = Point(x, y);
                    
                } else if(
                    c.r == 0 && c.g == 1 && c.b == 0
                ) {
                    spawns[1] = Point(x, y);
                    
                }
                
            }
        }
        
    } al_unlock_bitmap(data_bmp);
    
}


/* ----------------------------------------------------------------------------
 * Does the actual Turf War match.
 * Every iteration, Inklings ink the floor under them and move a bit.
 * Their movement is based on how aggressive they are.
 * They occasionally respawn, too.
 */
void Chapter::do_match() {
    for(size_t it = 0; it < chapter_data->n_simulation_iterations; ++it) {
        for(unsigned char i = 0; i < N_INKLINGS; ++i) {
            for(unsigned char team = 0; team < 2; ++team) {
                if(inklings[team][i].speed == 0) continue;
                inklings[team][i].ink();
                inklings[team][i].check_respawn();
                inklings[team][i].move();
            }
        }
        
        //DEBUG - Uncomment this to show the simulation being made.
        /*al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(arena_bmp, 0, 0, 0);
        for(unsigned char i = 0; i < N_INKLINGS; ++i) {
            for(unsigned char team = 0; team < 2; ++team) {
                al_draw_filled_rectangle(
                    inklings[team][i].pos.x - 2,
                    inklings[team][i].pos.y - 2,
                    inklings[team][i].pos.x + 2,
                    inklings[team][i].pos.y + 2,
                    ink_colors[team]
                );
            }
        }
        al_rest(0.03);
        al_flip_display();*/
    }
    
    for(size_t t = 0; t < 3; ++t) {
        blotch_generators[t].ink(this);
    }
    
    for(size_t t = 0; t < 2; ++t) {
        ink(spawns[t], SPAWN_RADIUS, t);
    }
}


/* ----------------------------------------------------------------------------
 * Calculates the percentages of turf that belong to team A, team B,
 * and neither. Places them on real_percentages.
 * These values range from 0 to 100.
 */
void Chapter::calculate_real_percentages() {
    unsigned long totals[3];
    for(size_t t = 0; t < 3; ++t) {
        totals[t] = 0;
    }
    
    for(size_t x = 0; x < width; ++x) {
        for(size_t y = 0; y < height; ++y) {
            Cell* c = &grid[x][y];
            
            if(c->type != CELL_TYPE_NORMAL) continue;
            totals[c->team]++;
        }
    }
    
    unsigned long grand_total = 0;
    for(size_t t = 0; t < 3; ++t) {
        grand_total += totals[t];
    }
    
    for(size_t t = 0; t < 3; ++t) {
        real_percentages[t] = (totals[t] / (float) grand_total) * 100;
    }
}


/* ----------------------------------------------------------------------------
 * Renders the final match result onto the result_bmp bitmap.
 */
void Chapter::render() {
    ALLEGRO_BITMAP* old_target_bitmap = al_get_target_bitmap();
    al_set_target_bitmap(result_bmp);
    al_lock_bitmap(
        result_bmp, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_READWRITE
    );
    
    for(size_t x = 0; x < width; ++x) {
        for(size_t y = 0; y < height; ++y) {
            ALLEGRO_COLOR c;
            unsigned char team = grid[x][y].team;
            if(team == TEAM_NONE) {
                c = al_map_rgba(0, 0, 0, 0);
            } else {
                c = ink_colors[team];
            }
            al_put_pixel(x, y, c);
        }
    }
    
    al_unlock_bitmap(result_bmp);
    al_set_target_bitmap(old_target_bitmap);
    
}


/* ----------------------------------------------------------------------------
 * Marks a circle on the arena as belonging to a team (or unclaimed).
 * where:  Central point of the circle.
 * radius: Radius of the circle.
 * team:   Team ID.
 */
void Chapter::ink(const Point &where, const float radius, const size_t team) {
    for(int dx = -radius; dx <= radius; ++dx) {
        for(int dy = -radius; dy <= radius; ++dy) {
            if(sqrt((float) (dx * dx + dy * dy)) <= radius) {
                ink(where + Point(dx, dy), team);
            }
        }
    }
}


/* ----------------------------------------------------------------------------
 * Marks a specific grid cell as belonging to a team (or unclaimed).
 * where: Grid position.
 * team:  Team ID.
 */
void Chapter::ink(const Point &where, const size_t team) {
    if(is_valid(where, true)) {
        grid[floor(where.x)][floor(where.y)].ink(team);
    }
}


/* ----------------------------------------------------------------------------
 * Checks whether a given cell is valid for movement or inking.
 * where:      Grid position.
 * for_inking: If true, checks if inking is possible.
 *   Else, checks if movement is possible.
 */
bool Chapter::is_valid(const Point &where, const bool for_inking) {
    if(
        where.x < 0 || where.x >= width ||
        where.y < 0 || where.y >= height ||
        grid[where.x][where.y].type == CELL_TYPE_VOID
    ) {
        return false;
    }
    
    if(
        for_inking &&
        grid[where.x][where.y].type == CELL_TYPE_UNINKABLE
    ) {
        return false;
    }
    
    return true;
}
