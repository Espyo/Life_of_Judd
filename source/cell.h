#ifndef INCLUDED_CELL_H
#define INCLUDED_CELL_H

#include <cstddef>


/* ----------------------------------------------------------------------------
 * Type of cell. Determines how ink and Inklings react to it.
 */
enum CELL_TYPE {
    CELL_TYPE_NORMAL,    //Can be inked and walked on.
    CELL_TYPE_UNINKABLE, //Cannot be inked, but can be walked on.
    CELL_TYPE_VOID,      //Cannot be inked or walked on.
};


/* ----------------------------------------------------------------------------
 * Information about a cell in the arena's grid.
 */
struct Cell {
    //Type of content. Use CELL_TYPE.
    unsigned char type;
    
    //ID of the team that owns this cell (or unclaimed).
    unsigned char team;
    
    Cell();
    void ink(const unsigned char team_nr);
    
};


#endif //ifndef INCLUDED_CELL_H
