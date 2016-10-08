#include "game_state.h"


/* ----------------------------------------------------------------------------
 * Constructs a game state.
 */
Game_State::Game_State(Game* game) :
    game(game) {
    
    
}


/* ----------------------------------------------------------------------------
 * Destroys a game state.
 */
Game_State::~Game_State() {
}


/* ----------------------------------------------------------------------------
 * Constructs a game state manager.
 */
Game_State_Manager::Game_State_Manager() :
    cur_state(nullptr) {
    
    
}


/* ----------------------------------------------------------------------------
 * Destroys a game state manager.
 */
Game_State_Manager::~Game_State_Manager() {
    for(auto s = states.begin(); s != states.end(); s++) {
        delete s->second;
    }
}


/* ----------------------------------------------------------------------------
 * Returns the current game state.
 */
Game_State* Game_State_Manager::get_current_state() {
    return cur_state;
}


/* ----------------------------------------------------------------------------
 * Registers a new game state.
 * id:      Its ID.
 * pointer: Pointer to an instance of the new state's class.
 */
void Game_State_Manager::register_state(const size_t id, Game_State* pointer) {
    states[id] = pointer;
}


/* ----------------------------------------------------------------------------
 * Changes the current state. This unloads the previous one and
 * loads the new one.
 */
void Game_State_Manager::change_state(const size_t new_state_id) {
    if(cur_state) cur_state->unload();
    cur_state = states[new_state_id];
    cur_state->load();
}
