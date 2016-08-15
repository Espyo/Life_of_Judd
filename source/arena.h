#ifndef INCLUDED_ARENA_H
#define INCLUDED_ARENA_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "blotch_generator.h"
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
    Blotch_Generator blotch_gen[3];
    
    Inkling inklings[2][N_INKLINGS];
    Point spawns[2];
    ALLEGRO_COLOR ink_colors[2];
    
    float real_percentages[3];
    
    ALLEGRO_BITMAP* arena_bmp;
    ALLEGRO_BITMAP* background_bmp;
    ALLEGRO_BITMAP* result_bmp;
    
    Arena();
    void load();
    void do_match();
    void render();
    void calculate_real_percentages();
    
    
    void ink(const Point where, const float radius, const size_t team);
    void ink(const Point where, const size_t team);
    bool is_valid(const Point where, const bool for_inking);
};


#endif //ifndef INCLUDED_ARENA_H
