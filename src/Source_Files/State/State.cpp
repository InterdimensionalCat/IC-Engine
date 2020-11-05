#include "include.h"
#include "State.h"
#include "StateManager.h"
#include "InputHandle.h"


State::State(std::shared_ptr<StateManager> p) : parent(p) {

}

State::~State() {

}