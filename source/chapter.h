#ifndef INCLUDED_CHAPTER_H
#define INCLUDED_CHAPTER_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "blotch_generator.h"
#include "chapter_data.h"
#include "cell.h"
#include "const.h"
#include "inkling.h"
#include "point.h"

using namespace std;

struct Chapter {
private:
    void generate_data();
    void get_data_from_bmp(ALLEGRO_BITMAP* data_bmp);
    
public:
    Chapter_Data* chapter_data;
    
    size_t width;
    size_t height;
    vector<vector<Cell> > grid;
    
    Inkling inklings[2][N_INKLINGS];
    ALLEGRO_COLOR ink_colors[2];
    Point spawns[2];
    float spawn_dist;
    
    float real_percentages[3];
    
    ALLEGRO_BITMAP* arena_bmp;
    ALLEGRO_BITMAP* background_bmp;
    ALLEGRO_BITMAP* result_bmp;
    
    Chapter();
    void load(
        ALLEGRO_BITMAP* arena_bmp, ALLEGRO_BITMAP* data_bmp,
        ALLEGRO_BITMAP* bg_bmp
    );
    void do_match();
    void render();
    void calculate_real_percentages();
    
    
    void ink(const Point where, const float radius, const size_t team);
    void ink(const Point where, const size_t team);
    bool is_valid(const Point where, const bool for_inking);
};


#endif //ifndef INCLUDED_CHAPTER_H
