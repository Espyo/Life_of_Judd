#include "cell.h"
#include "const.h"


Cell::Cell() :
    type(CELL_TYPE_NORMAL),
    team(TEAM_NONE) {
    
    
}


void Cell::ink(const unsigned char team_nr) {
    team = team_nr;
}
