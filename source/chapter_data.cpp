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
    data.difficulty = DIFFICULTY_BEGINNER;
    data.name = "Chapter 1: First Day on the Job";
    data.arena_nr = 0;
    data.ink_colors[0] = al_map_rgb(16,  160, 192);
    data.ink_colors[1] = al_map_rgb(208, 144, 48);
    
    /*
     * Max size is around these many characters (40):
     *  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
     */
    
    data.story.push_back(
        data.name + "\n"
        "May 8th, 2013\n"
        " \n"
        "Mrrow... Judd here."
    );
    data.story.push_back(
        "Several years ago, there was this thing\n"
        "called the \"Great Turf War\". In it,\n"
        "Inklings and Octarians fought for territory."
    );
    data.story.push_back(
        "I was there, too. It was up to me to\n"
        "judge which team inked the most turf.\n"
        "I've always been purretty good at that, purr..."
    );
    data.story.push_back(
        "Well, I'm no hisstory teacher, so enough\n"
        "of that. Fast-furward to the present, the\n"
        "Inklings chose to make a sport out of it.\n"
    );
    data.story.push_back(
        "Two teams of professionals must ink an arena\n"
        "as much as they can, and when the time\n"
        "is up, the winner is the team that\n"
        "inked the most turf."
    );
    data.story.push_back(
        "So, they made me the judge of this new sport.\n"
        "And today is the very furst day!\n"
        "They said the only thing I need to do\n"
        "is show up at the end, and judge the turf."
    );
    data.story.push_back(
        "Of course it won't be easy.\n"
        "It's a cat-eats-cat world out there, after all.\n"
        "I was told I'd be fired if I got it wrong.\n"
        "Mrrow, these Inklings are really passionate\n"
        "about this thing, huh?\n"
    );
    data.story.push_back(
        "When the match is over, they send analysis\n"
        "reports to some department inside the\n"
        "committee, where they examine, with purrfect\n"
        "accuracy, how much each team covered.\n"
        "They can even tell how much went uncovered!"
    );
    data.story.push_back(
        "They need me to pick a winner right after\n"
        "the match, so that the competitors don't have\n"
        "to wait weeks for the real results. But since\n"
        "the committee can know the exact statistics,\n"
        "they'll know if I goofed up..."
    );
    data.story.push_back("#arena");
    data.story.push_back(
        "Speaking of goofy, the competitors are here.\n"
        "Boy, do those equipments look ridiculous.\n"
        "But I have to admit, this whole thing\n"
        "has potential. Let's see how they do, then..."
    );
    data.story.push_back("#ink");
    data.story.push_back(
        "That was... Purretty exciting!\n"
        "Oh, it's my turn. So, let's see...\n"
        "They told me all I had to do was\n"
        "pick which of the two teams\n"
        "got the most turf. Here goes!"
    );
    
    data.n_simulation_iterations = 10000;
    
    for(size_t t = 0; t < 2; ++t) {
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0001;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0001;
        }
    }
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        data.inklings[0][i].speed = 3;
        data.inklings[1][i].speed = 2;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[0].team = TEAM_1;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[1].team = TEAM_2;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    data.blotch_generators[2].team = TEAM_NONE;
    
    v.push_back(data);
    
    return v;
}
