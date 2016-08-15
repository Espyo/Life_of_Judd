#include <algorithm>

#include "arena.h"
#include "blotch_generator.h"
#include "utils.h"

using namespace std;


Blotch_Generator::Blotch_Generator() :
    team(0),
    min_blotch_size(0),
    max_blotch_size(0),
    min_blotches(0),
    max_blotches(0) {
    
}


vector<Point> Blotch_Generator::generate_blotch() {
    struct Point_Info {
        Point p;
        unsigned char n_neighbors;
        bool neighbors[4];
        Point_Info() :
            n_neighbors(0) {
            
            neighbors[0] = false; //Right.
            neighbors[1] = false; //Top.
            neighbors[2] = false; //Left.
            neighbors[3] = false; //Bottom.
        }
        void add_neighbor(const unsigned char pos) {
            n_neighbors++;
            neighbors[pos] = true;
        }
        size_t get_random_free_pos() {
            size_t p = randomi(0, 4 - n_neighbors - 1);
            for(size_t n = 0; n < 4; ++n) {
                if(neighbors[n]) continue;
                if(p == 0) return n;
                --p;
            }
            return 0;
        }
    };
    
    vector<Point_Info> info;
    vector<Point> final_points;
    
    size_t n_points = randomi(min_blotch_size, max_blotch_size);
    if(n_points == 0) return final_points;
    
    Point_Info start;
    start.p = Point(0, 0);
    info.push_back(start);
    
    vector<size_t> neighbor_candidates;
    neighbor_candidates.push_back(0);
    
    for(size_t p = 1; p < n_points; ++p) {
    
        Point_Info new_info;
        
        //Find a neighbor for this point.
        size_t candidate_nr = randomi(0, neighbor_candidates.size() - 1);
        Point_Info* candidate = &info[neighbor_candidates[candidate_nr]];
        size_t pos = candidate->get_random_free_pos();
        if(pos == 0) {
            new_info.p = candidate->p + Point(1, 0);
        } else if(pos == 1) {
            new_info.p = candidate->p + Point(0, -1);
        } else if(pos == 2) {
            new_info.p = candidate->p + Point(-1, 0);
        } else {
            new_info.p = candidate->p + Point(0, 1);
        }
        candidate->add_neighbor(pos);
        
        //Check if this point has neighbors (although we already know
        //it has at least the neighbor it connected to just now).
        for(size_t i = 0; i < info.size(); ++i) {
            if(info[i].p == new_info.p + Point(1, 0)) {
                new_info.add_neighbor(0);
            } else if(info[i].p == new_info.p + Point(0, -1)) {
                new_info.add_neighbor(1);
            } else if(info[i].p == new_info.p + Point(-1, 0)) {
                new_info.add_neighbor(2);
            } else if(info[i].p == new_info.p + Point(0, 1)) {
                new_info.add_neighbor(3);
            }
            if(new_info.n_neighbors == 4) break;
        }
        
        info.push_back(new_info);
        
        //Update the list of candidates.
        neighbor_candidates.clear();
        for(size_t i = 0; i < info.size(); ++i) {
            if(info[i].n_neighbors < 4) {
                neighbor_candidates.push_back(i);
            }
        }
    }
    
    for(size_t i = 0; i < info.size(); ++i) {
        final_points.push_back(info[i].p);
    }
    
    return final_points;
}


vector<Point> Blotch_Generator::pick_starting_points(
    Arena* arena, const size_t amount
) {

    //First, count how many non-team cells there are.
    size_t n_valid_cells = 0;
    Cell* cell = NULL;
    for(size_t x = 0; x < arena->width; ++x) {
        for(size_t y = 0; y < arena->height; ++y) {
            cell = &arena->grid[x][y];
            if(cell->type == CELL_TYPE_NORMAL && cell->team != team) {
                n_valid_cells++;
            }
        }
    }
    
    //Now, pick random ones from that list.
    vector<size_t> chosen_spots;
    for(size_t n = 0; n < amount; ++n) {
        chosen_spots.push_back(randomi(0, n_valid_cells));
    }
    
    //For optimization purposes, sort the list.
    sort(chosen_spots.begin(), chosen_spots.end());
    
    //Now, go through the grid again, and get the X/Y of the chosen spots.
    vector<Point> final_points;
    size_t next_number = 0;
    size_t cur_spot = 0;
    bool done = false;
    for(size_t x = 0; x < arena->width; ++x) {
        for(size_t y = 0; y < arena->height; ++y) {
            cell = &arena->grid[x][y];
            if(cell->type == CELL_TYPE_NORMAL && cell->team != team) {
                next_number++;
            }
            if(chosen_spots[cur_spot] == next_number - 1) {
                final_points.push_back(Point(x, y));
                cur_spot++;
                if(cur_spot == amount) {
                    done = true;
                    break;
                }
            }
        }
        if(done == true) break;
    }
    
    return final_points;
}


void Blotch_Generator::ink(Arena* arena) {
    size_t n_blotches = randomi(min_blotches, max_blotches);
    vector<Point> starting_points = pick_starting_points(arena, n_blotches);
    
    for(size_t b = 0; b < starting_points.size(); ++b) {
        vector<Point> points = generate_blotch();
        
        for(size_t p = 0; p < points.size(); ++p) {
            arena->ink(starting_points[b] + points[p], team);
        }
    }
}
