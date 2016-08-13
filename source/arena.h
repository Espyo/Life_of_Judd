#ifndef INCLUDED_ARENA_H
#define INCLUDED_ARENA_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "cell.h"
#include "const.h"
#include "inkling.h"
#include "point.h"

using namespace std;


struct Arena {
private:
    void get_data_from_bmp(ALLEGRO_BITMAP* data_bmp);
    
public:
    size_t width;
    size_t height;
    vector<vector<Cell> > grid;
    unsigned long n_simulation_iterations;
    
    Inkling inklings[N_TEAMS][N_INKLINGS];
    Point spawns[N_TEAMS];
    ALLEGRO_COLOR ink_colors[N_TEAMS];
    
    float real_percentages[N_TEAMS + 1]; //+1 for unclaimed turf.
    
    ALLEGRO_BITMAP* background_bmp;
    ALLEGRO_BITMAP* result_bmp;
    
    Arena();
    void load();
    void do_match();
    void render();
    void calculate_real_percentages();
    
    
    void ink(const Point where, const float radius, const size_t team);
    void ink(const Point where, const size_t team);
    bool is_valid(const Point where);
};


#endif //ifndef INCLUDED_ARENA_H
