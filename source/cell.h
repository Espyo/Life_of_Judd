#ifndef INCLUDED_CELL_H
#define INCLUDED_CELL_H

#include <cstddef>


enum CELL_CONTENTS {
    CELL_CONTENT_CLEAR,
    CELL_CONTENT_VOID,
    CELL_CONTENT_TEAM_BASE,
};


struct Cell {
    unsigned char content;
    
    Cell();
    void ink(const size_t team_nr);
    
};


#endif //ifndef INCLUDED_CELL_H
