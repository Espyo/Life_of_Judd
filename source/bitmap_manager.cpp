#include "bitmap_manager.h"
#include "const.h"


void Bitmap_Manager::load_bitmap(const string file_name) {
    bitmaps[file_name] =
        al_load_bitmap((GRAPHICS_FOLDER + "/" + file_name).c_str());
}


ALLEGRO_BITMAP* Bitmap_Manager::get_bitmap(const string file_name) {
    return bitmaps[file_name];
}
