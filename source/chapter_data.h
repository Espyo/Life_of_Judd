#ifndef INCLUDED_CHAPTER_DATA_H
#define INCLUDED_CHAPTER_DATA_H

#include <vector>

#include <allegro5/allegro.h>

#include "blotch_generator.h"
#include "const.h"
#include "inkling.h"

using namespace std;


struct Game;

/* ----------------------------------------------------------------------------
 * Data about a story mode chapter.
 * Can also be used to define a free play level.
 */
struct Chapter_Data {
    //Name. Used on the chapter selection and story intro.
    string name;
    
    //ID of the arena.
    size_t arena_nr;
    
    //Difficulty. Use DIFFICULTIES.
    unsigned char difficulty;
    
    //Story intro. A vector of blocks of text, with lines separated by \n.
    vector<string> story;
    
    //Number of iterations for the match simulation.
    size_t n_simulation_iterations;
    
    //If true, teams can be randomly swapped around for variety.
    bool can_switch_teams;
    
    //Blotch generator info.
    Blotch_Generator blotch_generators[3];
    
    //Colors of each team's ink.
    ALLEGRO_COLOR ink_colors[2];
    
    //Starting data for the Inklings on each team.
    Inkling inklings[2][N_INKLINGS];
    
    Chapter_Data();
};


Chapter_Data generate_random_chapter_data(Game* game);
vector<Chapter_Data> get_chapters();


#endif //ifndef INCLUDED_CHAPTER_H
