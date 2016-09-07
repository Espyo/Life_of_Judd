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
    const int x, const int cy, const int flags, const string &text,
    const float scale, const bool top_valign
) {
    vector<string> lines = split(text, "\n");
    int fh = al_get_font_line_height(font);
    int total_height = lines.size() * fh + (lines.size() - 1);
    int top =
        top_valign ? cy : cy - total_height * 0.5 * scale;
        
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, scale, scale);
    al_translate_transform(&transform, x, top);
    ALLEGRO_TRANSFORM old_transform;
    al_copy_transform(&old_transform, al_get_current_transform());
    al_use_transform(&transform); {
    
        for(size_t l = 0; l < lines.size(); ++l) {
            float line_y = (fh + 1) * l;
            al_draw_text(
                font, darken_color(color, 0.25), 2, line_y + 2, flags,
                lines[l].c_str()
            );
            al_draw_text(
                font, color, 0, line_y, flags, lines[l].c_str()
            );
        }
        
    } al_use_transform(&old_transform);
}


string f2s(const float f) {
    std::stringstream s;
    s << std::fixed << ::setprecision(1) << f;
    return s.str();
}


string i2s(const long long i) {
    return to_string(i);
}


ALLEGRO_BITMAP* load_png_or_jpg(const string path) {
    ALLEGRO_BITMAP* b =
        al_load_bitmap((path + ".png").c_str());
    if(b) return b;
    return al_load_bitmap((path + ".jpg").c_str());
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


string rp(
    const string s1, const string s2,
    const string s3, const string s4
) {
    size_t n_strings = s3.empty() ? 2 : s4.empty() ? 3 : 4;
    
    size_t pick = randomi(0, n_strings - 1);
    if(pick == 0) return s1;
    if(pick == 1) return s2;
    if(pick == 2) return s3;
    return s4;
}


/* ----------------------------------------------------------------------------
 * Splits a string into several substrings, by the specified delimiter.
 * text:        The string to split.
 * del:         The delimiter. Default is space.
 * inc_empty:   If true, include empty substrings on the vector.
   * i.e. if two delimiters come together in a row,
   * keep an empty substring between.
 * inc_del:     If true, include the delimiters on the vector as a substring.
 */
vector<string> split(
    string text, const string &del, const bool inc_empty, const bool inc_del
) {
    vector<string> v;
    size_t pos;
    size_t del_size = del.size();
    
    do {
        pos = text.find(del);
        if (pos != string::npos) {  //If it DID find the delimiter.
            //Get the text between the start and the delimiter.
            string sub = text.substr(0, pos);
            
            //Add the text before the delimiter to the vector.
            if(sub != "" || inc_empty)
                v.push_back(sub);
                
            //Add the delimiter to the vector, but only if requested.
            if(inc_del)
                v.push_back(del);
                
            //Delete everything before the delimiter,
            //including the delimiter itself, and search again.
            text.erase(text.begin(), text.begin() + pos + del_size);
        }
    } while (pos != string::npos);
    
    //Text after the final delimiter.
    //(If there is one. If not, it's just the whole string.)
    
    //If it's a blank string,
    //only add it if we want empty strings.
    if (text != "" || inc_empty) {
        v.push_back(text);
    }
    
    return v;
}
