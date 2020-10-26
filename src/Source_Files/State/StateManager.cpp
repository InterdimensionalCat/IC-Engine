#include "include.h"
#include "StateManager.h"
#include "State.h"
#include "MenuState.h"
#include "GameState.h"

StateManager::StateManager(Game* in) : instance(in) {
	addState(new MenuState(this));
	addState(new GameState(this));
}

StateManager::~StateManager() {
	delete states.at("GAME");
	delete states.at("MENU");
	states.clear();
}

void StateManager::addState(State* state) {

	states.emplace(state->getName(), state);
	state->init();
	if (current == nullptr) {
		current = states.at(state->getName());
		current->enter();
	}
}

void StateManager::setState(const string &key) {
	if (states.find(key) != states.end()) {
		current->exit();
		current = states.at(key);
		current->enter();
	}
	else {
#ifdef debug_mode
		cerr << "State " << key << " does not exist!\n";
#endif
	}
}

void StateManager::tick(InputHandle* input) {
	current->tick(input);
}

void StateManager::draw(Renderer* renderer) {
	current->draw(renderer);
}