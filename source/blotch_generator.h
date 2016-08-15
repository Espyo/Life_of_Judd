#ifndef INCLUDED_BLOTCH_GENERATOR_H
#define INCLUDED_BLOTCH_GENERATOR_H


#include <vector>

#include "point.h"

using namespace std;


struct Arena;

struct Blotch_Generator {
private:
    vector<Point> pick_starting_points(Arena* arena, const size_t amount);
    vector<Point> generate_blotch();

public:
    unsigned char team;
    size_t min_blotch_size;
    size_t max_blotch_size;
    size_t min_blotches;
    size_t max_blotches;
    
    Blotch_Generator();
    void ink(Arena* arena);
};


#endif //ifndef INCLUDED_BLOTCH_GENERATOR_H
