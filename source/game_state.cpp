#include "game_state.h"


Game_State::Game_State(Game* game) :
    game(game) {
    
    
}


Game_State_Manager::Game_State_Manager() :
    cur_state(nullptr) {
    
    
}


Game_State* Game_State_Manager::get_current_state() {
    return cur_state;
}


void Game_State_Manager::register_state(const size_t id, Game_State* pointer) {
    states[id] = pointer;
}


void Game_State_Manager::change_state(const size_t new_state_id) {
    if(cur_state) cur_state->unload();
    cur_state = states[new_state_id];
    cur_state->load();
}
