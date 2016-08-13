#include "cell.h"


Cell::Cell() :
    content(CELL_CONTENT_VOID) {
    
    
}


void Cell::ink(const size_t team_nr) {
    content = CELL_CONTENT_TEAM_BASE + team_nr;
}
