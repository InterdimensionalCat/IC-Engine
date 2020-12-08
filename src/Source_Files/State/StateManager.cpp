#include "include.h"
#include "StateManager.h"
#include "State.h"
#include "MenuState.h"
#include "GameState.h"

StateManager::StateManager() {
	//addState(new MenuState(this));
	//addState(new GameState(this));
}

StateManager::~StateManager() {

}

void StateManager::addState(State* state) {

	states.emplace(state->getName(), std::unique_ptr<State>(state));
	state->init();
	if (current == nullptr) {
		current = states.at(state->getName()).get();
		current->enter();
	}
}

void StateManager::setState(const std::string &key) {
	if (states.find(key) != states.end()) {
		current->exit();
		current = states.at(key).get();
		current->enter();
	}
	else {
#ifdef debug_mode
		std::cerr << "State " << key << " does not exist!\n";
		throw std::exception();
#endif
	}
}

void StateManager::tick(InputHandle* input) {
	current->tick(input);
}

void StateManager::draw(Renderer* renderer) {
	current->draw(renderer);
}