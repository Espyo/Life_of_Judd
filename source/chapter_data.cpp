#include "chapter_data.h"
#include "const.h"
#include "game.h"
#include "utils.h"


/* ----------------------------------------------------------------------------
 * Constructs a chapter data info struct.
 */
Chapter_Data::Chapter_Data() :
    arena_nr(0),
    difficulty(DIFFICULTY_BEGINNER),
    n_simulation_iterations(0),
    can_switch_teams(true) {
    
}


/* ----------------------------------------------------------------------------
 * Generates random chapter data. Used for free play.
 */
Chapter_Data generate_random_chapter_data(Game* game) {
    Chapter_Data data;
    data.arena_nr = randomi(0, N_ARENAS - 1);
    data.n_simulation_iterations =
        randomi(1000, 2000);
        
    for(size_t t = 0; t < 2; ++t) {
        for(size_t i = 0; i < N_INKLINGS; ++i) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = randomf(0, 0.01);
            data.inklings[t][i].speed = randomf(5, 10);
            data.inklings[t][i].ink_radius = randomf(8, 15);
            data.inklings[t][i].respawn_chance = randomf(0, 0.005);
        }
    }
    
    for(size_t t = 0; t < 3; ++t) {
        data.blotch_generators[t].min_blotches = 0;
        data.blotch_generators[t].max_blotches = 50;
        data.blotch_generators[t].min_blotch_size = 1;
        data.blotch_generators[t].max_blotch_size = 20;
        data.blotch_generators[t].team = t;
    }
    
    size_t ink_pair = randomi(0, game->all_ink_colors.size() - 1);
    data.ink_colors[0] = game->all_ink_colors[ink_pair].first;
    data.ink_colors[1] = game->all_ink_colors[ink_pair].second;
    
    return data;
}


/* ----------------------------------------------------------------------------
 * Generates and returns chapter data for all story mode chapters.
 */
vector<Chapter_Data> get_chapters() {
    vector<Chapter_Data> v;
    
    //Chapter 1 ---------------------------------------------
    
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
        "declare the winner when it was all over.\n"
        "I've always liked doing that, purr..."
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
        "And today is the very first day!\n"
        "They said the only thing I need to do\n"
        "is show up at the end, and judge the turf."
    );
    data.story.push_back(
        "Of course it won't be easy.\n"
        "It's a cat-eats-cat world out there, after all.\n"
        "I was told I'd be fired if I got it wrong.\n"
        "Mrrow, the Inklings are really passionate\n"
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
        "to wait days for the real results. But since\n"
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
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.001;
            data.inklings[t][i].ink_radius = 6;
            data.inklings[t][i].respawn_chance = 0.0001;
        }
        data.inklings[0][i].speed = 6;
        data.inklings[1][i].speed = 4;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 2 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_BEGINNER;
    data.name = "Chapter 2: That Wasn't So Bad";
    data.arena_nr = 0;
    data.ink_colors[0] = al_map_rgb(16,  160, 192);
    data.ink_colors[1] = al_map_rgb(208, 144, 48);
    
    data.story.push_back(
        data.name + "\n"
        "May 15th, 2013\n"
        " \n"
        "Last week was a huge success!"
    );
    data.story.push_back(
        "The sport was well received, and my ability\n"
        "to tell the winner is as sharp as ever.\n"
        "I'm still nervous about messing up, but it's\n"
        "actually not that hard. At least, for now.\n"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "These players are pretty tame compared to\n"
        "the soldiers back in the Great Turf War.\n"
        "I don't think I even saw one of them swim up\n"
        "a single wall! Well, the sport is still in\n"
        "its early stages, I suppose."
    );
    data.story.push_back(
        "I'm sure that, as time goes by, everything\n"
        "will become more complex. I better be ready\n"
        "for it! But for now, it's time to focus on\n"
        "this match."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Meow, good game! Time to judge!"
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.002;
            data.inklings[t][i].ink_radius = 8;
            data.inklings[t][i].respawn_chance = 0.0002;
        }
        data.inklings[0][i].speed = 7;
        data.inklings[1][i].speed = 5.5;
    }
    
    data.blotch_generators[0].min_blotches = 2;
    data.blotch_generators[0].max_blotches = 2;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 2;
    data.blotch_generators[1].max_blotches = 2;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 3 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_BEGINNER;
    data.name = "Chapter 3: They're Getting Good";
    data.arena_nr = 0;
    data.ink_colors[0] = al_map_rgb(16,  160, 192);
    data.ink_colors[1] = al_map_rgb(208, 144, 48);
    
    data.story.push_back(
        data.name + "\n"
        "May 22th, 2013\n"
        " \n"
        "Time fur another match!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "I'm starting to like this. I'm even\n"
        "friends with some of the players\n"
        "and everything! Oh, but I'm not biased!\n"
        "...Right?"
    );
    data.story.push_back(
        "The players also know each other a bit better\n"
        "so they swapped some team members to\n"
        "better balance the matches, and make it\n"
        "more fun for everybody."
    );
    data.story.push_back(
        "What's more, they're all starting to get good!\n"
        "Talking about strategies in their spare time,\n"
        "thinking of creative ways to use the terrain...\n"
    );
    data.story.push_back(
        "That means they'll be inking a lot more,\n"
        "and on more equal amounts. It's going to be\n"
        "harder for me to judge, but hey,\n"
        "the challenge is fun too!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Yeah, it's certainly more even now than it\n"
        "was before! But I still know which team won."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0025;
            data.inklings[t][i].ink_radius = 9;
            data.inklings[t][i].respawn_chance = 0.00025;
            data.inklings[t][i].speed = 7;
        }
    }
    
    data.blotch_generators[0].min_blotches = 3;
    data.blotch_generators[0].max_blotches = 3;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 3;
    data.blotch_generators[1].max_blotches = 3;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 4 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_BEGINNER;
    data.name = "Chapter 4: Newcomers";
    data.arena_nr = 1;
    data.ink_colors[0] = al_map_rgb(112, 16,  224);
    data.ink_colors[1] = al_map_rgb(240, 255, 0);
    
    data.story.push_back(
        data.name + "\n"
        "May 29th, 2013\n"
        " \n"
        "Did I read this right?"
    );
    data.story.push_back(
        "The committee has assembled together a\n"
        "new arena! And on top of that, they're\n"
        "giving another group of eight players\n"
        "a try!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Well, it's certainly more complex than the\n"
        "other arena. It looks fun!\n"
        "Oh, but the players look puzzled.\n"
        "Is this arena too complex for them?"
    );
    data.story.push_back(
        "They're just starting out, and they\n"
        "have to be guinea pigs for the new arena...\n"
        "Hah, they'll get used to it!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "...Meow. I guess they don't have the hang\n"
        "of it yet!"
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.001;
            data.inklings[t][i].ink_radius = 4;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 2;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 5;
    data.blotch_generators[2].min_blotch_size = 3;
    data.blotch_generators[2].max_blotch_size = 5;
    
    v.push_back(data);
    
    //Chapter 5 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_BEGINNER;
    data.name = "Chapter 5: The Newcomers Are Getting Good";
    data.arena_nr = 1;
    data.ink_colors[0] = al_map_rgb(112, 16,  224);
    data.ink_colors[1] = al_map_rgb(240, 255, 0);
    
    data.story.push_back(
        data.name + "\n"
        "June 1st, 2013\n"
        " \n"
        "That new group is back again!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "The matches are becoming more frequent,\n"
        "the players are becoming more skilled,\n"
        "and the sport is evolving supurr-quickly."
    );
    data.story.push_back(
        "I even know the committee has plans to\n"
        "make the arenas look more natural,\n"
        "make the sport more accessible to everyone,\n"
        "and improve the backend tools and policies."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Not sure what they mean with the last one,\n"
        "but my gut feeling tells me I'll be involved...\n"
        "Oh, the match is over! Okay, let's see..."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.005;
            data.inklings[t][i].ink_radius = 8;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 6;
        }
    }
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 5;
    data.blotch_generators[0].min_blotch_size = 5;
    data.blotch_generators[0].max_blotch_size = 20;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 5;
    data.blotch_generators[1].min_blotch_size = 5;
    data.blotch_generators[1].max_blotch_size = 20;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 5;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 20;
    
    v.push_back(data);
    
    //Chapter 6 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 6: Doing the Math";
    data.arena_nr = 1;
    data.ink_colors[0] = al_map_rgb(176, 224, 32);
    data.ink_colors[1] = al_map_rgb(110, 6,   138);
    
    data.story.push_back(
        data.name + "\n"
        "January 22nd, 2014\n"
        " \n"
        "Mrrow... I knew it."
    );
    data.story.push_back(
        "Most of the changes the committee said\n"
        "they'll do are happening. They're still\n"
        "haggling with the government for the rights\n"
        "to build new arenas, but other than that,\n"
        "the big changes are happening today."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "The sport will now be played by professionals\n"
        "and casuals alike. Those that can afford it\n"
        "and are old enough, at least. But there's\n"
        "one huge change that affects me!"
    );
    data.story.push_back(
        "After the match, they want the players to not\n"
        "only know which team won, but by how much,\n"
        "too! It helps players better understand\n"
        "the game, their team, and their opponents.\n"
        "I get that, but..."
    );
    data.story.push_back(
        "Okay, according to their notes, I have to look\n"
        "at the turf that got inked, and decide how\n"
        "much belongs to each team. That's going to\n"
        "be tricky! But I should be able to pull it off."
    );
    data.story.push_back(
        "They also told me to ignore the uncovered\n"
        "turf entirely. Meow, well that's a relief.\n"
        "Finally, they told me I don't need to be\n"
        "perfect with my numbers. Just good enough\n"
        "for them to get an idea of their purrfurmance."
    );
    data.story.push_back(
        "Still, I've got to be careful about picking\n"
        "the right team! They give out the rewards to\n"
        "the players right after the battle, so they're\n"
        "depending on me to not pick the wrong team!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "The first match of this new scheme was\n"
        "played by a group of snobby Inklings. It\n"
        "shows! They don't know what they're doing!\n"
        "I hope I know what I'm doing though..."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.001;
            data.inklings[t][i].ink_radius = 5;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 2;
        data.inklings[1][i].speed = 3;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 0;
    data.blotch_generators[2].max_blotches = 0;
    data.blotch_generators[2].min_blotch_size = 0;
    data.blotch_generators[2].max_blotch_size = 0;
    
    v.push_back(data);
    
    //Chapter 7 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 7: Getting Used to Percentages";
    data.arena_nr = 1;
    data.ink_colors[0] = al_map_rgb(32,  131, 125);
    data.ink_colors[1] = al_map_rgb(223, 100, 26);
    
    data.story.push_back(
        data.name + "\n"
        "January 23rd, 2014\n"
        " \n"
        "That wasn't so tough."
    );
    data.story.push_back(
        "I even think this new percentage thingie\n"
        "makes more sense than just saying\n"
        "\"they win\". It's funner, too."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Looks like the players this time aren't\n"
        "professionals, but they're real go-getters!\n"
        "That one over there reminds me of Ammoses.\n"
        "Shared some good times with him. Used to\n"
        "be way skinnier back then, too."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Well, the two teams have different skill\n"
        "levels, I can tell that much. Not sure if\n"
        "that makes my job easier or harder, but\n"
        "I'm about to find out!"
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 8;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 4;
        data.inklings[1][i].speed = 6;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 4;
    data.blotch_generators[2].max_blotch_size = 8;
    
    v.push_back(data);
    
    //Chapter 8 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 8: The Great Outdoors";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(201, 52,  87);
    data.ink_colors[1] = al_map_rgb(4,   129, 136);
    
    data.story.push_back(
        data.name + "\n"
        "March 7th, 2014\n"
        " \n"
        "Sniiiiiiff... Purr..."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "We finally have an arena outdoors.\n"
        "I was tired of judging matches inside\n"
        "those stuffy bunkers with plastic walls,\n"
        "computers, and wires everywhere."
    );
    data.story.push_back(
        "The committee wants to create arenas in\n"
        "the middle of everyday locations, like\n"
        "highways, but for now, they have to stick\n"
        "with remote locations built exclusively\n"
        "for the sport."
    );
    data.story.push_back(
        "This place is more colorful. I hope it\n"
        "doesn't interfere with my ink color\n"
        "judging, mrrow. Players won't be able to\n"
        "ink that palm tree in the center room,\n"
        "according to what I was told."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 10;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 7;
        data.inklings[1][i].speed = 7.5;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 4;
    data.blotch_generators[2].max_blotch_size = 8;
    
    v.push_back(data);
    
    //Chapter 9 ---------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 9: The Pros Again";
    data.arena_nr = 0;
    data.ink_colors[0] = al_map_rgb(16,  160, 192);
    data.ink_colors[1] = al_map_rgb(208, 144, 48);
    
    data.story.push_back(
        data.name + "\n"
        "September 13th, 2014\n"
        " \n"
        "Oh, hey guys!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "It's those players again! The ones\n"
        "that played on the furst ever match\n"
        "of the then-new sport."
    );
    data.story.push_back(
        "I actually haven't seen them in a while.\n"
        "But they told me they spent a lot of time\n"
        "purracticing in private. What, did they go to\n"
        "a backyard and use mattresses as walls or\n"
        "something?"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Whatever it was, it paid off. They're really\n"
        "good at this, now!"
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 12;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 10;
        }
    }
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 10;
    data.blotch_generators[0].min_blotch_size = 5;
    data.blotch_generators[0].max_blotch_size = 10;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 10;
    data.blotch_generators[1].min_blotch_size = 5;
    data.blotch_generators[1].max_blotch_size = 10;
    data.blotch_generators[2].min_blotches = 3;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 10;
    data.blotch_generators[2].max_blotch_size = 20;
    
    v.push_back(data);
    
    //Chapter 10 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 10: A No-Show?";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(46,  12,  181);
    data.ink_colors[1] = al_map_rgb(248, 99,  0);
    
    data.story.push_back(
        data.name + "\n"
        "December 1st, 2014\n"
        " \n"
        "Brrr... Purr..."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "I hate Winter. It feels like I'm being\n"
        "frozen alive, which I certainly do not\n"
        "appreciate!"
    );
    data.story.push_back(
        "It's too cold to be battling on a beachside\n"
        "resort! There's no air-conditioning on these\n"
        "arenas. I hope they eventually change that,\n"
        "because right now, you'd have to be insane\n"
        "to play here at this time of year!"
    );
    data.story.push_back(
        "Looks like one Inkling got the right\n"
        "idea. The match is about to start, and that\n"
        "team only has three members. Must've\n"
        "stayed cozy at home..."
    );
    data.story.push_back(
        "The match really is going to begin! Is this\n"
        "even allowed? Oh, a Turf War Investigation\n"
        "and Normalization Entity representative\n"
        "just showed up. ...Okay, so the game has\n"
        "to start regardless. Well, good luck, trio!\n"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "That was painful to watch. I feel sorry\n"
        "for them, but I still have to give the\n"
        "final result."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 11;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 8;
        }
    }
    data.inklings[0][3].speed = 0;
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 10;
    data.blotch_generators[0].min_blotch_size = 5;
    data.blotch_generators[0].max_blotch_size = 10;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 10;
    data.blotch_generators[1].min_blotch_size = 5;
    data.blotch_generators[1].max_blotch_size = 10;
    data.blotch_generators[2].min_blotches = 3;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 10;
    data.blotch_generators[2].max_blotch_size = 20;
    
    v.push_back(data);
    
    //Chapter 11 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_INTERMEDIATE;
    data.name = "Chapter 11: Heard the News?";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(0,   126, 220);
    data.ink_colors[1] = al_map_rgb(225, 163, 7);
    
    data.story.push_back(
        data.name + "\n"
        "May 1st, 2015\n"
        " \n"
        "Oh, is that so?"
    );
    data.story.push_back(
        "That is so ambitious! The committee just\n"
        "announced that they're taking the sport\n"
        "into a new direction. It's going to leave\n"
        "its experimental phases, and is going to\n"
        "be called \"Splatoon\"."
    );
    data.story.push_back(
        "Furthermore, they're opening the sport to\n"
        "everybody, but with bigger focus on the kids.\n"
        "And they're making matches happen much\n"
        "more frequently, and on new arenas, too."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Looks like this match will be one of the last\n"
        "few I'll judge before the big change. I\n"
        "wonder if they are going to want me to\n"
        "do something different, too. Hehe, the\n"
        "last time I though that, it became true."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.004;
            data.inklings[t][i].ink_radius = 11;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 8;
        }
    }
    
    data.blotch_generators[0].min_blotches = 10;
    data.blotch_generators[0].max_blotches = 20;
    data.blotch_generators[0].min_blotch_size = 5;
    data.blotch_generators[0].max_blotch_size = 10;
    data.blotch_generators[1].min_blotches = 10;
    data.blotch_generators[1].max_blotches = 20;
    data.blotch_generators[1].min_blotch_size = 5;
    data.blotch_generators[1].max_blotch_size = 10;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 15;
    data.blotch_generators[2].max_blotch_size = 25;
    
    v.push_back(data);
    
    //Chapter 12 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 12: Splatoon Global Testfire";
    data.arena_nr = 3;
    data.ink_colors[0] = al_map_rgb(34,  140, 255);
    data.ink_colors[1] = al_map_rgb(232, 84,  7);
    
    data.story.push_back(
        data.name + "\n"
        "May 8th, 2015\n"
        " \n"
        "This is inkredible!"
    );
    data.story.push_back(
        "Kids from all over the place have gathered\n"
        "around for some matches of \"Turf War\".\n"
        "Apparently the sport is called \"Splatoon\",\n"
        "but this set of rules, where the winner is\n"
        "the team with the most ink, is \"Turf War\".\n"
    );
    data.story.push_back(
        "I wonder what the committee is planning with\n"
        "that. But no matter. Because Splatoon is now\n"
        "more elaborate than it ever was before,\n"
        "they need me to also announce how much\n"
        "terrain went uninked."
    );
    data.story.push_back(
        "It will help players better understand if\n"
        "they're really good at covering turf, or\n"
        "if they're just flopping about like fish\n"
        "out of water."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Honestly, I don't think this is going\n"
        "to be that hard. Out of the total\n"
        "territory on the arena, I just have\n"
        "to say how much team A got, how much\n"
        "team B got, and how much went uninked."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Oh, right. Those shiny plastic floors\n"
        "can't be inked. Those won't count for\n"
        "the percentages.\n"
        "Okay... Bring it on!"
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.002;
            data.inklings[t][i].ink_radius = 7;
            data.inklings[t][i].respawn_chance = 0.001;
            data.inklings[t][i].speed = 5;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 13 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 13: End of the Testfire";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(121, 149, 22);
    data.ink_colors[1] = al_map_rgb(110, 6,   138);
    
    data.story.push_back(
        data.name + "\n"
        "May 9th, 2015\n"
        " \n"
        "Oh, this weekend was just a testfire."
    );
    data.story.push_back(
        "Turns out they wanted to open up Turf War,\n"
        "but for now, only as a test. They're trying\n"
        "to see if people like it and gather\n"
        "statistics. All right, then."
    );
    data.story.push_back(
        "This testfire will close in a few hours,\n"
        "but they said they'll have another one in\n"
        "a few days, before opening Splatoon to\n"
        "the world."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.002;
            data.inklings[t][i].ink_radius = 6;
            data.inklings[t][i].respawn_chance = 0.0008;
            data.inklings[t][i].speed = 5.4;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 14 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 14: Testfire Part 2";
    data.arena_nr = 3;
    data.ink_colors[0] = al_map_rgb(207, 88,  27);
    data.ink_colors[1] = al_map_rgb(20,  20,  148);
    
    data.story.push_back(
        data.name + "\n"
        "May 23rd, 2015\n"
        " \n"
        "And it's back."
    );
    data.story.push_back(
        "The committee put the entire sport on hold\n"
        "for the sake of preparations. Today, there's\n"
        "a new testfire event, but this one will only\n"
        "last for one day."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "A lot of Inklings got around to try to\n"
        "squeeze in some more matches before this\n"
        "event is over. Look at those spry kids!"
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 6;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 5.8;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 15 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 15: Splatoon's Launch!";
    data.arena_nr = 4;
    data.ink_colors[0] = al_map_rgb(218, 55,  129);
    data.ink_colors[1] = al_map_rgb(237, 148, 8);
    
    data.story.push_back(
        data.name + "\n"
        "May 29th, 2015\n"
        " \n"
        "Okay, this is the real deal now!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Splatoon is meow officially public.\n"
        "There's a new arena, too. It's pretty\n"
        "neat seeing so many different players,\n"
        "and comparing Splatoon as it is now to the\n"
        "small little sport it was when it started."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Hmm... These new players still haven't\n"
        "gotten the hang of it. There's so much\n"
        "terrain left uninked! I'm sure that as\n"
        "time goes by, everybody will get more\n"
        "used to the game and arenas."
    );
    data.story.push_back(
        "Oh, speaking of getting used to arenas,\n"
        "I need to remember that those shiny\n"
        "blue crates cannot be inked."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.004;
            data.inklings[t][i].ink_radius = 7;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 6;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 16 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 16: Ranked Battle";
    data.arena_nr = 4;
    data.ink_colors[0] = al_map_rgb(200, 61,  121);
    data.ink_colors[1] = al_map_rgb(64,  157, 59);
    
    data.story.push_back(
        data.name + "\n"
        "June 5th, 2015\n"
        " \n"
        "I bet those eight came from Ranked Battle."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Today, a thing called \"Ranked Battle\" was\n"
        "made available. A lot of players flocked\n"
        "to that mode, where the winner is no longer\n"
        "determined by turf inked. I think each mode\n"
        "in Ranked Battle has different rules."
    );
    data.story.push_back(
        "Either way, since inking turf is not as\n"
        "impurrtant, I don't judge those matches.\n"
        "Players are still told that I give the\n"
        "final decision, but really, the scoring\n"
        "system speaks for itself."
    );
    data.story.push_back(
        "Speaking of inking a lot of turf,\n"
        "I remember some days back, when I thought\n"
        "to myself how little players ink in\n"
        "Turf War. Slowly but surely, that has\n"
        "been improving."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Meow! What?! That's barely inked at all!\n"
        "I could tell from their attitude that they\n"
        "came from playing a lot of Ranked Battle\n"
        "matches, and it shows!"
    );
    data.story.push_back(
        "Instead of focusing on inking turf for\n"
        "Turf War, these Inklings just tried\n"
        "splatting one another over and over!\n"
        "Keep it to Ranked Battle, guys!\n"
        "Well, I have to judge this match anyway..."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.5;
            data.inklings[t][i].ink_radius = 6;
            data.inklings[t][i].respawn_chance = 0.05;
            data.inklings[t][i].speed = 5;
        }
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 6;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 17 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 17: Splatting is Fun!";
    data.arena_nr = 4;
    data.ink_colors[0] = al_map_rgb(0,   126, 220);
    data.ink_colors[1] = al_map_rgb(225, 163, 7);
    
    data.story.push_back(
        data.name + "\n"
        "June 20th, 2015\n"
        " \n"
        "Ranked Battle really changed the ambiance."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Although players are learning to ink more\n"
        "and more, they're also learning to be\n"
        "aggressive. Some players go on hunts,\n"
        "and only ink the ground because it fills\n"
        "up their special weapon gauge."
    );
    data.story.push_back(
        "Being a splatter does have its advantages.\n"
        "If the opponents are constantly being\n"
        "splatted, they can't ink and win! Still,\n"
        "some players push it too far, while others\n"
        "just try their best to ink and score a victory."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Wow. This is a purrfect example of what I\n"
        "mean! That team kept splatting the other\n"
        "team, while they were trying to avoid them\n"
        "and ink a lot. But the first team tried\n"
        "really hard to keep stage control, too..."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].ink_radius = 7;
            data.inklings[t][i].speed = 6;
        }
        data.inklings[0][i].aggressiveness = 0.3;
        data.inklings[0][i].respawn_chance = 0.0005;
        data.inklings[1][i].aggressiveness = 0.005;
        data.inklings[1][i].respawn_chance = 0.005;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 18 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 18: Splatfest!";
    data.arena_nr = 3;
    data.ink_colors[0] = al_map_rgb(216, 64, 17);
    data.ink_colors[1] = al_map_rgb(65,  167, 130);
    
    data.story.push_back(
        data.name + "\n"
        "July 4th, 2015\n"
        " \n"
        "Meow! This is so fun!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "This \"Splatfest\" thing is awesome!\n"
        "The Squid Sisters are singing,\n"
        "the night gives the battles some funk,\n"
        "and players vote for their tastes with ink!"
    );
    data.story.push_back(
        "The furst subject of debate is\n"
        "\"Cats vs Dogs\". Mrrow, of course\n"
        "I would pick team Cats, but since I'm\n"
        "here to judge, not to play, I won't\n"
        "say anything on that matter."
    );
    
    data.n_simulation_iterations = 1500;
    data.can_switch_teams = false;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 12;
            data.inklings[t][i].respawn_chance = 0.0007;
        }
        data.inklings[0][i].speed = 7;
        data.inklings[1][i].speed = 8;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 19 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 19: Cats vs Dogs Results";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(46,  12,  181);
    data.ink_colors[1] = al_map_rgb(248, 99,  0);
    
    data.story.push_back(
        data.name + "\n"
        "July 5th, 2015\n"
        " \n"
        "Oh. Okay. Dogs won."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "I'm only a bit upset because, well,\n"
        "I'm a cat. Can't people appreciate\n"
        "a fluffy, kind, and smart companion\n"
        "nowadays, is that it?"
    );
    data.story.push_back(
        "Ah well. If I were a Team Cat member,\n"
        "I think I'd be more upset, since I'd miss\n"
        "out on some of those Super Sea Snails.\n"
        "I hope those players aren't salty. Splatfest\n"
        "Battles are all in good fun, right?"
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.003;
            data.inklings[t][i].ink_radius = 12;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 8;
        }
    }
    
    data.blotch_generators[0].min_blotches = 3;
    data.blotch_generators[0].max_blotches = 9;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 3;
    data.blotch_generators[1].max_blotches = 9;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 20 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 20: Missing Inklings...";
    data.arena_nr = 3;
    data.ink_colors[0] = al_map_rgb(207, 88,  27);
    data.ink_colors[1] = al_map_rgb(20,  20,  148);
    
    data.story.push_back(
        data.name + "\n"
        "July 20th, 2015\n"
        " \n"
        "An Inkling is missing again?"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "This is starting to happen a lot. I wonder\n"
        "what causes some players to just not\n"
        "show up? Is something wrong with the\n"
        "matchmaking system, or are they\n"
        "bailing out on purrpose?"
    );
    data.story.push_back(
        "...Huh? There are actually two Inklings\n"
        "missing? And they're both from the same\n"
        "team?! That's horrible! But the match\n"
        "just has to start, no matter what..."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Oh dear... They gave it their best, but..."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].ink_radius = 12;
            data.inklings[t][i].speed = 8;
        }
        data.inklings[0][i].aggressiveness = 0.02;
        data.inklings[1][i].aggressiveness = 0.03;
        data.inklings[0][i].respawn_chance = 0.07;
        data.inklings[1][i].respawn_chance = 0.003;
    }
    data.inklings[0][0].speed = 0;
    data.inklings[0][1].speed = 0;
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 3;
    data.blotch_generators[1].max_blotches = 9;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 21 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 21: Tide Park";
    data.arena_nr = 5;
    data.ink_colors[0] = al_map_rgb(0,   126, 220);
    data.ink_colors[1] = al_map_rgb(225, 163, 7);
    
    data.story.push_back(
        data.name + "\n"
        "August 15th, 2015\n"
        " \n"
        "Trees everywhere...!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "So they made Tide Park an arena, huh?\n"
        "It does look like a purretty fun place\n"
        "to duke it out on, that's for sure."
    );
    data.story.push_back(
        "All of the trees provide cover from\n"
        "enemy shots, but they also can't be\n"
        "inked. ...Which just makes my job\n"
        "harder. I'm going to have to take\n"
        "so many spots into account, now!"
    );
    data.story.push_back(
        "And of course, the big fountain in the\n"
        "center also can't be inked. And\n"
        "those thin street lights probably\n"
        "can't be inked either, since they're\n"
        "made of metal."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.001;
            data.inklings[t][i].ink_radius = 10;
            data.inklings[t][i].respawn_chance = 0.007;
            data.inklings[t][i].speed = 7;
        }
    }
    
    data.blotch_generators[0].min_blotches = 1;
    data.blotch_generators[0].max_blotches = 3;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 1;
    data.blotch_generators[1].max_blotches = 3;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 22 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 22: Missing Inklings!!!";
    data.arena_nr = 5;
    data.ink_colors[0] = al_map_rgb(32,  131, 125);
    data.ink_colors[1] = al_map_rgb(223, 100, 26);
    
    data.story.push_back(
        data.name + "\n"
        "September 1st, 2015\n"
        " \n"
        "Missing Inklings, again..."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "This is becoming a bit of a problem.\n"
        "Some Inklings just don't show up, for\n"
        "whatever reas-- huh?"
    );
    data.story.push_back(
        "The third team member also didn't show up?\n"
        "Meow! So, is that Inkling going to fight on\n"
        "her own, then?"
    );
    data.story.push_back(
        "Oh! She's quitting! And who can blame her,\n"
        "honestly? With friends like hers, who needs\n"
        "enemies, right?"
    );
    data.story.push_back(
        "Wait, but that means... The other team will\n"
        "fight alone! Am I really going to judge a\n"
        "match with only one team?"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "...Here I go, I guess. Before I recklessly give\n"
        "the final result, I better carefully check\n"
        "how much turf the missing team really has."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.03;
            data.inklings[t][i].ink_radius = 13;
            data.inklings[t][i].respawn_chance = 0;
            data.inklings[t][i].speed = 10;
        }
        data.inklings[0][i].speed = 0;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 23 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 23: Art vs Science";
    data.arena_nr = 2;
    data.ink_colors[0] = al_map_rgb(146, 8,   231);
    data.ink_colors[1] = al_map_rgb(247, 143, 46);
    data.can_switch_teams = false;
    
    data.story.push_back(
        data.name + "\n"
        "September 18th, 2015\n"
        " \n"
        "Now this is a hot topic!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Art or Science... I'm not quite sure\n"
        "which of the two I prefer.\n"
        "But those Inklings sure know what\n"
        "they're fighting for."
    );
    data.story.push_back(
        "In this corner, a creative bunch of\n"
        "Inklings with sparks in their eyes.\n"
        "They're great at making art, and painting\n"
        "like crazy is no hard task for them."
    );
    data.story.push_back(
        "In that corner, a group of calm and\n"
        "calculated players with a knack for\n"
        "getting things done right. And\n"
        "efficiently, too!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "So let's see, which of the two is\n"
        "best? Creative talent, or book smarts?"
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].ink_radius = 18;
            data.inklings[t][i].speed = 12;
        }
        data.inklings[0][i].aggressiveness = 0.001;
        data.inklings[0][i].respawn_chance = 0.01;
        data.inklings[1][i].aggressiveness = 0.004;
        data.inklings[1][i].respawn_chance = 0.005;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 2;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 20;
    data.blotch_generators[1].max_blotches = 30;
    data.blotch_generators[1].min_blotch_size = 8;
    data.blotch_generators[1].max_blotch_size = 15;
    data.blotch_generators[2].min_blotches = 5;
    data.blotch_generators[2].max_blotches = 10;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 24 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 24: Goofing Around";
    data.arena_nr = 5;
    data.ink_colors[0] = al_map_rgb(218, 55,  129);
    data.ink_colors[1] = al_map_rgb(237, 148, 8);
    
    data.story.push_back(
        data.name + "\n"
        "October 4th, 2015\n"
        " \n"
        "Aww, isn't that nice."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "As those eight Inklings were walking\n"
        "into the arena, they were smiling\n"
        "and laughing with one another,\n"
        "even though they were on opposite\n"
        "teams."
    );
    data.story.push_back(
        "Not like it's common for Inklings to be\n"
        "bitter towards the other team. It's just\n"
        "that, since Turf War is so popular, there\n"
        "are so many players, and since they don't\n"
        "know each other, friendliness is rare."
    );
    data.story.push_back(
        "So, these eight are probably close friends.\n"
        "And they have such a carefree and...\n"
        "mischievous attitude. Hmm, the match is\n"
        "about to start, so let me keep a\n"
        "close eye on this bunch."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Th-They didn't do a thing! They just\n"
        "repeatedly changed between a kid and\n"
        "a squid, and wobbled like that all\n"
        "over the place!"
    );
    data.story.push_back(
        "When the two teams got close, they\n"
        "just danced together and did weird\n"
        "stunts."
    );
    data.story.push_back(
        "The imagination of a young Inkling is\n"
        "truly a sight to behold. I guess you\n"
        "don't need to shoot ink just to\n"
        "have a good time."
    );
    data.story.push_back(
        "Well, this is going to be tricky to\n"
        "judge! They managed to place a few\n"
        "splotches here and there. Guess I'll\n"
        "go by those."
    );
    
    data.n_simulation_iterations = 500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].speed = 0;
        }
    }
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 20;
    data.blotch_generators[0].min_blotch_size = 1;
    data.blotch_generators[0].max_blotch_size = 20;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 20;
    data.blotch_generators[1].min_blotch_size = 1;
    data.blotch_generators[1].max_blotch_size = 20;
    data.blotch_generators[2].min_blotches = 0;
    data.blotch_generators[2].max_blotches = 0;
    data.blotch_generators[2].min_blotch_size = 0;
    data.blotch_generators[2].max_blotch_size = 0;
    
    v.push_back(data);
    
    //Chapter 25 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 25: One Brave Hero";
    data.arena_nr = 5;
    data.ink_colors[0] = al_map_rgb(34,  140, 255);
    data.ink_colors[1] = al_map_rgb(232, 84,  7);
    
    data.story.push_back(
        data.name + "\n"
        "November 11th, 2015\n"
        " \n"
        "This is starting to become normal."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "The match is about to start in just a\n"
        "minute, and some of the Inklings are\n"
        "missing. Oh, just as I say that, the\n"
        "fourth player of that team arrived. But..."
    );
    data.story.push_back(
        "The other team is missing all of its\n"
        "members except for one. If this match\n"
        "is a 1v4, that Inkling will probably not\n"
        "be very motivated to fight."
    );
    data.story.push_back(
        "Most of what that Inkling will be doing\n"
        "is ink turf already claimed by the other\n"
        "team. That leads to a lot of points, on\n"
        "the bright side!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Predictably, the match was a 1v4.\n"
        "Let's see how our lonesome hero\n"
        "managed..."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
        }
        data.inklings[0][i].aggressiveness = 0.01;
        data.inklings[0][i].ink_radius = 20;
        data.inklings[0][i].respawn_chance = 0.001;
        data.inklings[0][i].speed = 12;
    }
    data.inklings[1][0].speed = 0;
    data.inklings[1][1].speed = 0;
    data.inklings[1][2].speed = 0;
    data.inklings[1][3].aggressiveness = 0.05;
    data.inklings[1][3].ink_radius = 20;
    data.inklings[1][3].respawn_chance = 0.1;
    data.inklings[1][3].speed = 12;
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 20;
    data.blotch_generators[1].min_blotch_size = 1;
    data.blotch_generators[1].max_blotch_size = 20;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 5;
    data.blotch_generators[2].min_blotch_size = 2;
    data.blotch_generators[2].max_blotch_size = 5;
    
    v.push_back(data);
    
    //Chapter 26 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 26: Mouth-watering Fun!";
    data.arena_nr = 6;
    data.ink_colors[0] = al_map_rgb(200, 61,  121);
    data.ink_colors[1] = al_map_rgb(64,  157, 59);
    
    data.story.push_back(
        data.name + "\n"
        "January 12th, 2016\n"
        " \n"
        "Mrr-rrow! I LOVE this arena!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "My stomach's rumbling just by being here!\n"
        "But I can't interfere with the arena!\n"
        "I'll have to sit tight and simply look at\n"
        "what's happening."
    );
    data.story.push_back(
        "I'm starting to wonder if this arena is a\n"
        "blessing or a curse, now...\n"
        "I have to be strong! ...As I hope those\n"
        "glasses are! They better be ready to\n"
        "take a Splat Bomb explosion or two..."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.01;
            data.inklings[t][i].ink_radius = 10;
            data.inklings[t][i].respawn_chance = 0.007;
            data.inklings[t][i].speed = 7;
        }
    }
    
    data.blotch_generators[0].min_blotches = 1;
    data.blotch_generators[0].max_blotches = 3;
    data.blotch_generators[0].min_blotch_size = 2;
    data.blotch_generators[0].max_blotch_size = 5;
    data.blotch_generators[1].min_blotches = 1;
    data.blotch_generators[1].max_blotches = 3;
    data.blotch_generators[1].min_blotch_size = 2;
    data.blotch_generators[1].max_blotch_size = 5;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 27 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 27: Weird Warzone";
    data.arena_nr = 6;
    data.ink_colors[0] = al_map_rgb(46,  12,  181);
    data.ink_colors[1] = al_map_rgb(248, 99,  0);
    
    data.story.push_back(
        data.name + "\n"
        "February 19th, 2016\n"
        " \n"
        "I have a weird feeling about this one."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "The Inklings on that team clean up the\n"
        "opposing team's ink super-precisely.\n"
        "The other team, on the other paw,\n"
        "can't even be bothered."
    );
    data.story.push_back(
        "It's so nice that there are so many different\n"
        "types of personalities in the players that\n"
        "play Turf War. It helps remind that\n"
        "every one is not just a pawn in a game, but\n"
        "somebody with exact emotions and styles."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "...Too deep? Mrrow, I guess I do that when\n"
        "I'm hungry. Oh, and I got sidetracked, and\n"
        "now the match is done."
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
        }
        data.inklings[0][i].aggressiveness = 0.01;
        data.inklings[0][i].ink_radius = 20;
        data.inklings[0][i].respawn_chance = 0.01;
        data.inklings[0][i].speed = 12;
        data.inklings[1][i].aggressiveness = 0.01;
        data.inklings[1][i].ink_radius = 20;
        data.inklings[1][i].respawn_chance = 0.001;
        data.inklings[1][i].speed = 12;
    }
    
    data.blotch_generators[0].min_blotches = 40;
    data.blotch_generators[0].max_blotches = 50;
    data.blotch_generators[0].min_blotch_size = 40;
    data.blotch_generators[0].max_blotch_size = 70;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 0;
    data.blotch_generators[2].max_blotches = 0;
    data.blotch_generators[2].min_blotch_size = 0;
    data.blotch_generators[2].max_blotch_size = 0;
    
    v.push_back(data);
    
    //Chapter 28 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 28: No Fun Allowed";
    data.arena_nr = 6;
    data.ink_colors[0] = al_map_rgb(201, 52,  87);
    data.ink_colors[1] = al_map_rgb(4,   129, 136);
    
    data.story.push_back(
        data.name + "\n"
        "April 16th, 2016\n"
        " \n"
        "Oh, \"squidbaggers\"."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Those Inklings over there are already\n"
        "\"squidbagging\" before even entering\n"
        "the arena. That is what it's called,\n"
        "right? \"Squidbagging\"? When kids go to\n"
        "and from squid form really quickly?"
    );
    data.story.push_back(
        "The other team just saw them flop like\n"
        "crazy and decided to do the same!\n"
        "Isn't it magical when an entire group of\n"
        "people get the same fun idea without\n"
        "even sharing a single word?"
    );
    data.story.push_back(
        "Uhm, I take that back. Not the entire group.\n"
        "That single Inkling has such a horrible frown...\n"
        "Don't tell me..."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "Yep, that Inkling went alone while the others\n"
        "frolicked about harmlessly. Her team won\n"
        "but she's raging like crazy!\n"
        "What's the matter? Not having fun?\n"
        "That's what you get fur being a party-pooper!"
    );
    data.story.push_back(
        "...Wow. That was harsh. That Inkling was only\n"
        "trying to follow the game's objective.\n"
        "Squidbagging is fun, but when other people\n"
        "don't want to join and suffer from it, that's\n"
        "no good. I hope more people realize that."
    );
    data.story.push_back(
        "What am I, the thought police? People should\n"
        "do whatever they want. I just don't like\n"
        "seeing anybody get upset, is all."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].speed = 0;
        }
    }
    data.inklings[1][3].aggressiveness = 0.05;
    data.inklings[1][3].ink_radius = 10;
    data.inklings[1][3].respawn_chance = 0;
    data.inklings[1][3].speed = 10;
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 2;
    data.blotch_generators[2].max_blotches = 5;
    data.blotch_generators[2].min_blotch_size = 2;
    data.blotch_generators[2].max_blotch_size = 5;
    
    v.push_back(data);
    
    //Chapter 29 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 29: Duel";
    data.arena_nr = 4;
    data.ink_colors[0] = al_map_rgb(218, 55,  129);
    data.ink_colors[1] = al_map_rgb(237, 148, 8);
    
    data.story.push_back(
        data.name + "\n"
        "June 24th, 2016\n"
        " \n"
        "So...is this match going to be canceled?"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "Because nobody is here ye--\n"
        "Oh, one Inkling is finally here.\n"
        "The match will start any second now."
    );
    data.story.push_back(
        "Good, another Inkling. Now, where are\n"
        "the rest? Don't tell me this will be a\n"
        "one-on-one!\n"
        "Looks like it! The match is startiiing...\n"
        "Now!"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "That was actually one of the most interesting\n"
        "fights I've seen in a long while.\n"
        "This will be fun to judge."
    );
    
    data.n_simulation_iterations = 1000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].speed = 0;
        }
    }
    for(size_t t = 0; t < 2; ++t) {
        data.inklings[t][0].aggressiveness = 0.1;
        data.inklings[t][0].ink_radius = 6;
        data.inklings[t][0].respawn_chance = 0.005;
        data.inklings[t][0].speed = 7;
    }
    
    data.blotch_generators[0].min_blotches = 0;
    data.blotch_generators[0].max_blotches = 0;
    data.blotch_generators[0].min_blotch_size = 0;
    data.blotch_generators[0].max_blotch_size = 0;
    data.blotch_generators[1].min_blotches = 0;
    data.blotch_generators[1].max_blotches = 0;
    data.blotch_generators[1].min_blotch_size = 0;
    data.blotch_generators[1].max_blotch_size = 0;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Chapter 30 --------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "Chapter 30: Callie vs Marie";
    data.arena_nr = 6;
    data.ink_colors[0] = al_map_rgb(175, 22,  172);
    data.ink_colors[1] = al_map_rgb(113, 218, 12);
    data.can_switch_teams = false;
    
    data.story.push_back(
        data.name + "\n"
        "July 22nd, 2016\n"
        " \n"
        "The final one?!"
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "This is it... The final Splatfest...\n"
        "It feels like it started just yesterday.\n"
        "And to top it off, you have to choose\n"
        "between the two Squid Sisters!"
    );
    data.story.push_back(
        "Good thing I'm not playing, because I\n"
        "couldn't possibly pick! Callie plays\n"
        "with me a lot, but Marie lets me sleep\n"
        "on her lap. This Splatfest is just cruel!\n"
    );
    data.story.push_back(
        "Is this really the final Splatfest?\n"
        "Are they cutting off support for the\n"
        "sport? What will this mean for the future?"
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "But...I guess the spirit of Turf War will\n"
        "live on. Splatfest or not, Inklings are\n"
        "always aching to ink turf in teams.\n"
        "Oh well. Whatever happens, happens.\n"
        "Let's judge!"
    );
    
    data.n_simulation_iterations = 1500;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.01;
            data.inklings[t][i].ink_radius = 18;
            data.inklings[t][i].respawn_chance = 0.01;
        }
        data.inklings[0][i].speed = 12;
        data.inklings[1][i].speed = 12.7;
    }
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 10;
    data.blotch_generators[0].min_blotch_size = 10;
    data.blotch_generators[0].max_blotch_size = 20;
    data.blotch_generators[1].min_blotches = 10;
    data.blotch_generators[1].max_blotches = 20;
    data.blotch_generators[1].min_blotch_size = 15;
    data.blotch_generators[1].max_blotch_size = 25;
    data.blotch_generators[2].min_blotches = 10;
    data.blotch_generators[2].max_blotches = 20;
    data.blotch_generators[2].min_blotch_size = 5;
    data.blotch_generators[2].max_blotch_size = 10;
    
    v.push_back(data);
    
    //Credits -----------------------------------------------
    
    data = Chapter_Data();
    
    data.difficulty = DIFFICULTY_EXPERT;
    data.name = "~Thanks For Playing!~";
    data.arena_nr = 0;
    data.ink_colors[0] = al_map_rgb(200, 61,  121);
    data.ink_colors[1] = al_map_rgb(64,  157, 59);
    
    data.story.push_back(
        "Present day\n"
        " \n"
        "Splatoon..."
    );
    data.story.push_back(
        "Splatfest might be over, but players\n"
        "from all over the globe still get\n"
        "together to play. As long as they're\n"
        "having fun, that's all that matters,\n"
        "right?"
    );
    data.story.push_back(
        "I wonder if they'll ever unveil a\n"
        "\"Splatoon 2\". Maybe they'll fix\n"
        "some of the small problems they found\n"
        "during the development of Splatoon?"
    );
    data.story.push_back(
        "Or maybe they'll focus solely on new\n"
        "mechanics. Oh, or even allowing four\n"
        "teams to square it out! Who's to say?"
    );
    data.story.push_back(
        "Either way, this is my job now, and\n"
        "all things considered, it's pretty good!\n"
        "I just chill, watch as the game evolves\n"
        "and sometimes raise a flag to one team\n"
        "or the other."
    );
    data.story.push_back(
        "There are some wacky matches here and\n"
        "there, but I think most of the interesting\n"
        "ones are already over. There's not much else\n"
        "to say. Now, my life is to just judge,\n"
        "judge, judge! Plain and simple."
    );
    data.story.push_back(
        "#arena"
    );
    data.story.push_back(
        "#devtext"
    );
    data.story.push_back(
        "With that said, I'd like to thank you for\n"
        "playing \"A Day in the Life of Judd\"!\n"
        "I hope I was able to entertain you for some\n"
        "hours with this simple game."
    );
    data.story.push_back(
        "Have you tried out free mode yet? There's\n"
        "unlimited fun to be had there. Oh, you can\n"
        "also try to get a perfect score of 100 on\n"
        "each chapter, actually!"
    );
    data.story.push_back(
        "You won't get anything from it other than\n"
        "a sense of achievement, though.\n"
        "If you want to know more about the game\n"
        "or its development, try the included\n"
        "readme text file."
    );
    data.story.push_back(
        "Hmm... I can't really create an epilogue\n"
        "without making it into a chapter in the\n"
        "eyes of the game. I mean, I can, but\n"
        "I don't feel like coding that in."
    );
    data.story.push_back(
        "#ink"
    );
    data.story.push_back(
        "So instead, have this weird match!\n"
        "I'll let you try it now. Take care,\n"
        "and once again, thanks for playing!\n"
        "                      --Espyo"
    );
    
    data.n_simulation_iterations = 1;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].speed = 0;
        }
    }
    
    data.blotch_generators[0].min_blotches = 200;
    data.blotch_generators[0].max_blotches = 300;
    data.blotch_generators[0].min_blotch_size = 10;
    data.blotch_generators[0].max_blotch_size = 50;
    data.blotch_generators[1].min_blotches = 200;
    data.blotch_generators[1].max_blotches = 300;
    data.blotch_generators[1].min_blotch_size = 10;
    data.blotch_generators[1].max_blotch_size = 50;
    data.blotch_generators[2].min_blotches = 0;
    data.blotch_generators[2].max_blotches = 0;
    data.blotch_generators[2].min_blotch_size = 0;
    data.blotch_generators[2].max_blotch_size = 0;
    
    v.push_back(data);
    
    //Final setup -------------------------------------------
    
    for(size_t c = 0; c < v.size(); ++c) {
        for(size_t t = 0; t < 3; ++t) {
            v[c].blotch_generators[t].team = t;
        }
    }
    
    return v;
}
