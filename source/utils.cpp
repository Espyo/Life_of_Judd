#include <algorithm>
#include <iomanip>

#include "utils.h"


ALLEGRO_COLOR darken_color(ALLEGRO_COLOR color, const float ratio) {
    color.r *= ratio;
    color.g *= ratio;
    color.b *= ratio;
    return color;
}


void draw_shadowed_text(
    ALLEGRO_FONT* font, ALLEGRO_COLOR color,
    const int x, const int y, const int flags, const string &text
) {
    int shifted_y = y - (al_get_font_line_height(font) - al_get_font_ascent(font));
    al_draw_text(
        font, darken_color(color, 0.25), x + 2, shifted_y + 2, flags, text.c_str()
    );
    al_draw_text(
        font, color, x, shifted_y, flags, text.c_str()
    );
}


string f2s(const float f) {
    std::stringstream s;
    s << std::fixed << ::setprecision(1) << f;
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
