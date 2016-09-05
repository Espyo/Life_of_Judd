#include "chapter_data.h"
#include "const.h"
#include "game.h"
#include "utils.h"

Chapter_Data::Chapter_Data() :
    arena_nr(0),
    difficulty(DIFFICULTY_BEGINNER),
    n_simulation_iterations(0) {
    
}


Chapter_Data generate_random_chapter_data(Game* game) {
    Chapter_Data data;
    data.arena_nr = randomi(0, N_ARENAS - 1);
    data.n_simulation_iterations =
        randomi(10000, 50000);
        
    for(size_t t = 0; t < 2; ++t) {
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = randomf(0, 0.005);
            data.inklings[t][i].speed = randomf(1, 5);
            data.inklings[t][i].ink_radius = randomf(3, 6);
            data.inklings[t][i].respawn_chance = randomf(0, 0.005);
        }
    }
    
    for(size_t t = 0; t < 3; ++t) {
        data.blotch_generators[t].min_blotches = 0;
        data.blotch_generators[t].max_blotches = 20;
        data.blotch_generators[t].min_blotch_size = 1;
        data.blotch_generators[t].max_blotch_size = 100;
        data.blotch_generators[t].team = t;
    }
    
    size_t ink_pair = randomi(0, game->all_ink_colors.size() - 1);
    data.ink_colors[0] = game->all_ink_colors[ink_pair].first;
    data.ink_colors[1] = game->all_ink_colors[ink_pair].second;
    
    return data;
}


vector<Chapter_Data> get_chapters() {
    vector<Chapter_Data> v;
    
    //TODO
    Chapter_Data data;
    data.name = "Chapter 1: First Day on the Job";
    data.arena_nr = 0;
    data.difficulty = DIFFICULTY_BEGINNER;
    
    data.story.push_back(
        "This is a test.\n"
        "Line #2"
    );
    data.story.push_back(
        "Box #2. Showing the map..."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Showing the ink now..."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "All done."
    );
    
    data.n_simulation_iterations = 10000;
    
    for(size_t t = 0; t < 2; ++t) {
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0005;
            data.inklings[t][i].speed = 4;
            data.inklings[t][i].ink_radius = 4;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
    }
    
    data.blotch_generators[0].min_blotches = 10;
    data.blotch_generators[0].max_blotches = 20;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 50;
    data.blotch_generators[0].team = 0;
    data.blotch_generators[1].min_blotches = 10;
    data.blotch_generators[1].max_blotches = 20;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 50;
    data.blotch_generators[1].team = 1;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 2;
    data.blotch_generators[2].max_blotch_size = 50;
    data.blotch_generators[2].team = 2;
    
    data.ink_colors[0] = al_map_rgb(175, 22, 172);
    data.ink_colors[1] = al_map_rgb(113, 218, 12);
    
    v.push_back(data);
    
    return v;
}
