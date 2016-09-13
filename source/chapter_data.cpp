#include "chapter_data.h"
#include "const.h"
#include "game.h"
#include "utils.h"

Chapter_Data::Chapter_Data() :
    arena_nr(0),
    difficulty(DIFFICULTY_BEGINNER),
    n_simulation_iterations(0),
    can_switch_teams(true) {
    
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
    //TODO
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0001;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0001;
        }
        data.inklings[0][i].speed = 3;
        data.inklings[1][i].speed = 2;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0002;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0002;
        }
        data.inklings[0][i].speed = 3.5;
        data.inklings[1][i].speed = 2.75;
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
        "Time for another match!"
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.00025;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.00025;
            data.inklings[t][i].speed = 3.5;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0001;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 1;
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
        "and the sport is evolving super-quickly."
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0005;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 3;
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
        "for them to get an idea of their performance."
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0001;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 1;
        data.inklings[1][i].speed = 1.5;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 1.5;
        data.inklings[1][i].speed = 2.5;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.0005;
        }
        data.inklings[0][i].speed = 3.5;
        data.inklings[1][i].speed = 3.75;
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
        "that played on the first ever match\n"
        "of the then-new sport."
    );
    data.story.push_back(
        "I actually haven't seen them in a while.\n"
        "But they told me they spent a lot of time\n"
        "practicing in private. What, did they go to\n"
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
    
    data.n_simulation_iterations = 15000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 3;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 4;
        }
    }
    
    data.blotch_generators[0].min_blotches = 3;
    data.blotch_generators[0].max_blotches = 5;
    data.blotch_generators[0].min_blotch_size = 10;
    data.blotch_generators[0].max_blotch_size = 15;
    data.blotch_generators[1].min_blotches = 3;
    data.blotch_generators[1].max_blotches = 5;
    data.blotch_generators[1].min_blotch_size = 10;
    data.blotch_generators[1].max_blotch_size = 15;
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
        "even allowed? Oh, a committee representative\n"
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
    
    data.n_simulation_iterations = 15000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 3;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 4;
        }
    }
    data.inklings[0][3].speed = 0;
    
    data.blotch_generators[0].min_blotches = 3;
    data.blotch_generators[0].max_blotches = 5;
    data.blotch_generators[0].min_blotch_size = 10;
    data.blotch_generators[0].max_blotch_size = 15;
    data.blotch_generators[1].min_blotches = 3;
    data.blotch_generators[1].max_blotches = 5;
    data.blotch_generators[1].min_blotch_size = 10;
    data.blotch_generators[1].max_blotch_size = 15;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0004;
            data.inklings[t][i].ink_radius = 3;
            data.inklings[t][i].respawn_chance = 0.0005;
            data.inklings[t][i].speed = 4;
        }
    }
    
    data.blotch_generators[0].min_blotches = 5;
    data.blotch_generators[0].max_blotches = 8;
    data.blotch_generators[0].min_blotch_size = 10;
    data.blotch_generators[0].max_blotch_size = 20;
    data.blotch_generators[1].min_blotches = 5;
    data.blotch_generators[1].max_blotches = 8;
    data.blotch_generators[1].min_blotch_size = 10;
    data.blotch_generators[1].max_blotch_size = 20;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0002;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.001;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0002;
            data.inklings[t][i].ink_radius = 2.2;
            data.inklings[t][i].respawn_chance = 0.0008;
            data.inklings[t][i].speed = 2.2;
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 2.4;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 2.4;
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
        "Splatoon is now officially public.\n"
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0004;
            data.inklings[t][i].ink_radius = 2.5;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 2.5;
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
        "important, I don't judge those matches.\n"
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
    
    data.n_simulation_iterations = 10000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.5;
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].respawn_chance = 0.05;
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
    
    data.n_simulation_iterations = 15000;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].ink_radius = 2;
            data.inklings[t][i].speed = 2.5;
        }
        data.inklings[0][i].aggressiveness = 0.1;
        data.inklings[0][i].respawn_chance = 0.0005;
        data.inklings[1][i].aggressiveness = 0.01;
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
        "The first subject of debate is\n"
        "\"Cats vs Dogs\". Mrrow, of course\n"
        "I would pick team Cats, but since I'm\n"
        "here to judge, not to play, I won't\n"
        "say anything on that matter."
    );
    
    data.n_simulation_iterations = 15000;
    data.can_switch_teams = false;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 3;
            data.inklings[t][i].respawn_chance = 0.0007;
        }
        data.inklings[0][i].speed = 2.8;
        data.inklings[1][i].speed = 3.2;
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
    data.name = "Chapter 19: Splatfest Results";
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
    
    data.n_simulation_iterations = 15000;
    data.can_switch_teams = false;
    
    for(size_t i = 0; i < N_INKLINGS; ++i) {
        for(size_t t = 0; t < 2; ++t) {
            data.inklings[t][i] = Inkling(NULL, Point(0, 0), t);
            data.inklings[t][i].aggressiveness = 0.0003;
            data.inklings[t][i].ink_radius = 3;
            data.inklings[t][i].respawn_chance = 0.0007;
            data.inklings[t][i].speed = 3.5;
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
    
    //Final setup -------------------------------------------
    
    for(size_t c = 0; c < v.size(); ++c) {
        for(size_t t = 0; t < 3; ++t) {
            v[c].blotch_generators[t].team = t;
        }
    }
    
    return v;
}
