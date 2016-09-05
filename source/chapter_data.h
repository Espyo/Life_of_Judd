#ifndef INCLUDED_CHAPTER_DATA_H
#define INCLUDED_CHAPTER_DATA_H

#include <vector>

#include <allegro5/allegro.h>

#include "blotch_generator.h"
#include "const.h"
#include "inkling.h"

using namespace std;


struct Game;

struct Chapter_Data {
    string name;
    size_t arena_nr;
    unsigned char difficulty;
    vector<string> story;
    size_t n_simulation_iterations;
    Blotch_Generator blotch_generators[3];
    ALLEGRO_COLOR ink_colors[2];
    Inkling inklings[2][N_INKLINGS];
    
    Chapter_Data();
};


Chapter_Data generate_random_chapter_data(Game* game);
vector<Chapter_Data> get_chapters();


#endif //ifndef INCLUDED_CHAPTER_H
