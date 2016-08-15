#ifndef INCLUDED_UTILS_H
#define INCLUDED_UTILS_H

#include <sstream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "point.h"

using namespace std;


ALLEGRO_COLOR darken_color(ALLEGRO_COLOR, const float ratio);
void draw_shadowed_text(
    ALLEGRO_FONT* font, ALLEGRO_COLOR color,
    const int x, const int y, const int flags, const string &text
);
string f2s(const float f);
string i2s(const long long i);
float randomf(float min, float max);
int randomi(int min, int max);


#endif //ifndef INCLUDED_UTILS_H
