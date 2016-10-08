#ifndef INCLUDED_BLOTCH_GENERATOR_H
#define INCLUDED_BLOTCH_GENERATOR_H


#include <vector>

#include "point.h"

using namespace std;


struct Chapter;

/* ----------------------------------------------------------------------------
 * A blotch generator is in charge of inking random blotches of ink
 * on the arena's grid.
 */
struct Blotch_Generator {
private:
    vector<Point> pick_starting_points(Chapter* chapter, const size_t amount);
    vector<Point> generate_blotch();
    
public:
    //ID of the team this generator belongs to.
    unsigned char team;
    
    //Each blotch is random within this size.
    size_t min_blotch_size;
    size_t max_blotch_size;
    
    //Generate a random number of blotches within this limit.
    size_t min_blotches;
    size_t max_blotches;
    
    Blotch_Generator();
    void ink(Chapter* chapter);
};


#endif //ifndef INCLUDED_BLOTCH_GENERATOR_H
