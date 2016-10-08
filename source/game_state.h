#ifndef INCLUDED_GAME_STATE_H
#define INCLUDED_GAME_STATE_H

#include <map>

#include <allegro5/allegro.h>

using namespace std;


struct Game;


/* ----------------------------------------------------------------------------
 * A game state's base class.
 * Contains code for what to do on timer tick logic, drawing, loading,
 * unloading, etc.
 * States are changed with the state manager.
 */
class Game_State {
protected:
    Game* game;
    
public:
    //Code to run when the state is switched to.
    virtual void load() = 0;
    //Code to run on a mouse event.
    virtual void handle_mouse(ALLEGRO_EVENT ev) = 0;
    //Code to run on timer tick.
    virtual void do_logic() = 0;
    //Code to run when drawing to the screen.
    virtual void do_drawing() = 0;
    //Code to run when the state is switched from.
    virtual void unload() = 0;
    
    explicit Game_State(Game* game);
    virtual ~Game_State() = 0;
};


/* ----------------------------------------------------------------------------
 * Keeps a list of the game's states, and manages
 * changing between them.
 */
struct Game_State_Manager {
private:
    map<size_t, Game_State*> states;
    Game_State* cur_state;
    
public:

    Game_State* get_current_state();
    void register_state(const size_t id, Game_State* pointer);
    void change_state(const size_t new_state_id);
    
    Game_State_Manager();
    ~Game_State_Manager();
};


#endif //ifndef INCLUDED_GAME_STATE_H
