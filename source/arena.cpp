#include <algorithm>

#include "arena.h"


Arena::Arena() :
    width(0),
    height(0),
    n_simulation_iterations(0),
    result_bmp(nullptr) {
    
    
}


void Arena::load() {

    ALLEGRO_BITMAP* data_bmp = al_load_bitmap((GRAPHICS_FOLDER + "/arenas/1_data.png").c_str()); //TODO
    background_bmp = al_load_bitmap((GRAPHICS_FOLDER + "/arenas/1.jpg").c_str()); //TODO
    
    get_data_from_bmp(data_bmp);
    al_destroy_bitmap(data_bmp);
    
    result_bmp = al_create_bitmap(width, height);
    
    //TODO this is hammered in for testing.
    
    n_simulation_iterations = 10000;
    blotch_gen[0].min_blotches = 10;
    blotch_gen[0].max_blotches = 20;
    blotch_gen[0].min_blotch_size = 2;
    blotch_gen[0].max_blotch_size = 50;
    blotch_gen[0].team = 0;
    blotch_gen[1].min_blotches = 10;
    blotch_gen[1].max_blotches = 20;
    blotch_gen[1].min_blotch_size = 2;
    blotch_gen[1].max_blotch_size = 50;
    blotch_gen[1].team = 1;
    blotch_gen[2].min_blotches = 10;
    blotch_gen[2].max_blotches = 20;
    blotch_gen[2].min_blotch_size = 2;
    blotch_gen[2].max_blotch_size = 50;
    blotch_gen[2].team = 2;
    
    ink_colors[0] = al_map_rgb(175, 22, 172);
    ink_colors[1] = al_map_rgb(113, 218, 12);
    
    for(size_t t = 0; t < 2; ++t) {
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            inklings[t][i] = Inkling(this, spawns[t], t);
            inklings[t][i].aggressiveness = 0.0005;
            inklings[t][i].speed = 4;
            inklings[t][i].ink_radius = 4;
            inklings[t][i].respawn_chance = 0.0005;
        }
    }
    
}


void Arena::get_data_from_bmp(ALLEGRO_BITMAP* data_bmp) {
    width = al_get_bitmap_width(data_bmp);
    height = al_get_bitmap_height(data_bmp);
    
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


void Arena::do_match() {
    for(size_t it = 0; it < n_simulation_iterations; ++it) {
        for(unsigned char i = 0; i < N_INKLINGS; ++i) {
            for(unsigned char team = 0; team < 2; ++team) {
                if(inklings[team][i].speed == 0) continue;
                inklings[team][i].ink();
                inklings[team][i].check_respawn();
                inklings[team][i].move();
            }
        }
    }
    
    for(size_t t = 0; t < 3; ++t) {
        blotch_gen[t].ink(this);
    }
    
    for(size_t t = 0; t < 2; ++t) {
        ink(spawns[t], SPAWN_RADIUS, t);
    }
}


void Arena::calculate_real_percentages() {
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


void Arena::render() {
    al_set_target_bitmap(result_bmp);
    al_lock_bitmap(
        result_bmp, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_READWRITE
    );
    
    for(size_t x = 0; x < width; ++x) {
        for(size_t y = 0; y < height; ++y) {
            ALLEGRO_COLOR c;
            unsigned char team = grid[x][y].team;
            if(team == TEAM_NONE) {
                c = {0.0, 0.0, 0.0, 0.0};
            } else {
                c = ink_colors[team];
            }
            al_put_pixel(x, y, c);
        }
    }
    
    al_unlock_bitmap(result_bmp);
    
}


void Arena::ink(const Point where, const float radius, const size_t team) {
    for(int dx = -radius; dx <= radius; ++dx) {
        for(int dy = -radius; dy <= radius; ++dy) {
            if(sqrt(dx * dx + dy * dy) <= radius) {
                ink(where + Point(dx, dy), team);
            }
        }
    }
}


void Arena::ink(const Point where, const size_t team) {
    if(is_valid(where, true)) {
        grid[floor(where.x)][floor(where.y)].ink(team);
    }
}


bool Arena::is_valid(const Point where, const bool for_inking) {
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
