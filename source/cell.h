#ifndef INCLUDED_CELL_H
#define INCLUDED_CELL_H

#include <cstddef>


enum CELL_TYPE {
    CELL_TYPE_NORMAL,
    CELL_TYPE_UNINKABLE,
    CELL_TYPE_VOID,
};


struct Cell {
    unsigned char type;
    unsigned char team;
    
    Cell();
    void ink(const unsigned char team_nr);
    
};


#endif //ifndef INCLUDED_CELL_H
