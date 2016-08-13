#ifndef INCLUDED_UTILS_H
#define INCLUDED_UTILS_H

#include <sstream>
#include <string>

#include <allegro5/allegro.h>

#include "point.h"

using namespace std;


ALLEGRO_COLOR darken_color(ALLEGRO_COLOR, const float ratio);
string f2s(const float f);
string i2s(const long long i);
float randomf(float min, float max);
int randomi(int min, int max);


#endif //ifndef INCLUDED_UTILS_H
