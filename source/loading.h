#ifndef INCLUDED_LOADING_H
#define INCLUDED_LOADING_H

#include "game_state.h"


class Loading : public Game_State {
private:


public:
    virtual void load();
    virtual void handle_mouse(ALLEGRO_EVENT ev);
    virtual void do_logic();
    virtual void do_drawing();
    virtual void unload();
    
    Loading(Game* game);
};


#endif //ifndef INCLUDED_LOADING_H
