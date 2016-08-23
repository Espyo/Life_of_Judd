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
    const int x, const int cy, const int flags, const string &text,
    const float scale = 1.0
);
string f2s(const float f);
string i2s(const long long i);
float randomf(float min, float max);
int randomi(int min, int max);
string rp(
    const string s1, const string s2,
    const string s3 = "", const string s4 = ""
);
vector<string> split(
    string text, const string &del = " ", const bool inc_empty = false,
    const bool inc_del = false
);


#endif //ifndef INCLUDED_UTILS_H
