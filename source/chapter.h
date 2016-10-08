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

/* ----------------------------------------------------------------------------
 * Struct responsible for data about the currently running chapter.
 * Also applies for the current free play level.
 * Contains info about the match that will happen, the grid's state, etc.
 */
struct Chapter {
private:
    void generate_data();
    void get_data_from_bmp(ALLEGRO_BITMAP* data_bmp);
    
public:
    //Generation data to base this chapter on.
    Chapter_Data* chapter_data;
    
    //Total dimensions of the grid.
    size_t width;
    size_t height;
    
    //The grid, with info about what's inked, and where.
    vector<vector<Cell> > grid;
    
    //Data about the match's Inklings.
    Inkling inklings[2][N_INKLINGS];
    
    //Each team's color.
    ALLEGRO_COLOR ink_colors[2];
    
    //Each team's blotch generator.
    Blotch_Generator blotch_generators[3];
    
    //Each team's spawn points.
    Point spawns[2];
    
    //Distance between each spawn point.
    float spawn_dist;
    
    //Percentages of team A's turf, team B's, and unclaimed.
    float real_percentages[3];
    
    //Bitmap used for the arena.
    ALLEGRO_BITMAP* arena_bmp;
    
    //Bitmap to repeat as the background.
    ALLEGRO_BITMAP* background_bmp;
    
    //Bitmap with the ink. This is overlaid on the arena bitmap.
    ALLEGRO_BITMAP* result_bmp;
    
    Chapter();
    void load(
        ALLEGRO_BITMAP* arena_bmp, ALLEGRO_BITMAP* data_bmp,
        ALLEGRO_BITMAP* bg_bmp
    );
    void do_match();
    void render();
    void calculate_real_percentages();
    
    
    void ink(const Point &where, const float radius, const size_t team);
    void ink(const Point &where, const size_t team);
    bool is_valid(const Point &where, const bool for_inking);
};


#endif //ifndef INCLUDED_CHAPTER_H
