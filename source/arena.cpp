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
    
    ink_colors[0] = al_map_rgb(175, 22, 172);
    ink_colors[1] = al_map_rgb(113, 218, 12);
    
    for(size_t t = 0; t < N_TEAMS; ++t) {
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
    
        for(size_t x = 0; x < width; ++x) {
            for(size_t y = 0; y < height; ++y) {
                ALLEGRO_COLOR c = al_get_pixel(data_bmp, x, y);
                
                if(
                    c.r == 1 && c.g == 1 && c.b == 1
                ) {
                    grid[x][y].content = CELL_CONTENT_CLEAR;
                    
                } else if(
                    c.r == 1 && c.g == 0 && c.b == 0
                ) {
                    spawns[0] = Point(x, y);
                    grid[x][y].content = CELL_CONTENT_CLEAR;
                    
                } else if(
                    c.r == 0 && c.g == 1 && c.b == 0
                ) {
                    spawns[1] = Point(x, y);
                    grid[x][y].content = CELL_CONTENT_CLEAR;
                    
                }
                
            }
        }
        
    } al_unlock_bitmap(data_bmp);
    
    
}


void Arena::do_match() {
    for(size_t it = 0; it < n_simulation_iterations; ++it) {
        for(unsigned char i = 0; i < N_INKLINGS; ++i) {
            for(unsigned char team = 0; team < N_TEAMS; ++team) {
                if(inklings[team][i].speed == 0) continue;
                inklings[team][i].ink();
                inklings[team][i].check_respawn();
                inklings[team][i].move();
            }
        }
    }
    
    for(size_t t = 0; t < N_TEAMS; ++t) {
        ink(spawns[t], SPAWN_RADIUS, t);
    }
}


void Arena::calculate_real_percentages() {
    unsigned long totals[N_TEAMS + 1];
    for(size_t t = 0; t < N_TEAMS + 1; ++t) {
        totals[t] = 0;
    }
    
    for(size_t x = 0; x < width; ++x) {
        for(size_t y = 0; y < height; ++y) {
            Cell* c = &grid[x][y];
            
            if(c->content == CELL_CONTENT_CLEAR) {
                totals[N_TEAMS]++;
            } else if(c->content >= CELL_CONTENT_TEAM_BASE) {
                totals[c->content - CELL_CONTENT_TEAM_BASE]++;
            }
        }
    }
    
    unsigned long grand_total = 0;
    for(size_t t = 0; t < N_TEAMS + 1; ++t) {
        grand_total += totals[t];
    }
    
    for(size_t t = 0; t < N_TEAMS + 1; ++t) {
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
            unsigned char content = grid[x][y].content;
            if(content >= CELL_CONTENT_TEAM_BASE) {
                c = ink_colors[grid[x][y].content - CELL_CONTENT_TEAM_BASE];
            } else {
                c = {0.0, 0.0, 0.0, 0.0};
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
    if(is_valid(where)) {
        grid[floor(where.x)][floor(where.y)].ink(team);
    }
}


bool Arena::is_valid(const Point where) {
    if(
        where.x < 0 || where.x >= width ||
        where.y < 0 || where.y >= height ||
        grid[where.x][where.y].content == CELL_CONTENT_VOID
    ) {
        return false;
    }
    return true;
}
