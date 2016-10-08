#ifndef INCLUDED_LOADING_H
#define INCLUDED_LOADING_H

#include "game_state.h"


/* ----------------------------------------------------------------------------
 * Loading screen game state.
 * This is the brief moment between the main menu and the action.
 */
class Loading : public Game_State {
private:


public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    explicit Loading(Game* game);
    ~Loading();
};


#endif //ifndef INCLUDED_LOADING_H
