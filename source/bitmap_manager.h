#ifndef INCLUDED_BITMAP_MANAGER_H
#define INCLUDED_BITMAP_MANAGER_H

#include <map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;


struct Bitmap_Manager {
private:
    map<string, ALLEGRO_BITMAP*> bitmaps;
    
public:

    void load_bitmap(const string file_name);
    ALLEGRO_BITMAP* get_bitmap(const string file_name);
};


#endif //ifndef INCLUDED_BITMAP_MANAGER_H
