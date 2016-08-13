#ifndef INCLUDED_GAME_STATE_H
#define INCLUDED_GAME_STATE_H

#include <map>

#include <allegro5/allegro.h>

using namespace std;


struct Game;


class Game_State {
protected:
    Game* game;
    
public:
    virtual void load() = 0;
    virtual void handle_mouse(ALLEGRO_EVENT ev) = 0;
    virtual void do_logic() = 0;
    virtual void do_drawing() = 0;
    virtual void unload() = 0;
    
    Game_State(Game* game);
};


struct Game_State_Manager {
private:
    map<size_t, Game_State*> states;
    Game_State* cur_state;
    
public:

    Game_State* get_current_state();
    void register_state(const size_t id, Game_State* pointer);
    void change_state(const size_t new_state_id);
    
    Game_State_Manager();
};


#endif //ifndef INCLUDED_GAME_STATE_H
