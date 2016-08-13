#include <algorithm>
#include <iomanip>

#include "utils.h"


ALLEGRO_COLOR darken_color(ALLEGRO_COLOR color, const float ratio) {
    color.r *= ratio;
    color.g *= ratio;
    color.b *= ratio;
    return color;
}


string f2s(const float f) {
    std::stringstream s;
    s << std::fixed << ::setprecision(2) << f;
    return s.str();
}


string i2s(const long long i) {
    return to_string(i);
}


/* ----------------------------------------------------------------------------
 * Returns a random float between the provided range, inclusive.
 */
float randomf(float min, float max) {
    if(min == max) return min;
    if(min > max) swap(min, max);
    return (float) rand() / ((float) RAND_MAX / (max - min)) + min;
}


/* ----------------------------------------------------------------------------
 * Returns a random integer between the provided range, inclusive.
 */
int randomi(int min, int max) {
    if(min == max) return min;
    if(min > max) swap(min, max);
    return ((rand()) % (max - min + 1)) + min;
}
