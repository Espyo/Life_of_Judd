#include "cell.h"
#include "const.h"


/* ----------------------------------------------------------------------------
 * Constructs a grid cell.
 */
Cell::Cell() :
    type(CELL_TYPE_NORMAL),
    team(TEAM_NONE) {
    
    
}


/* ----------------------------------------------------------------------------
 * Inks the cell with a given team's ink (or no team).
 */
void Cell::ink(const unsigned char team_nr) {
    team = team_nr;
}
