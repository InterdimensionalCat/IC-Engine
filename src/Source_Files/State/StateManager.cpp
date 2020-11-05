#include "include.h"
#include "StateManager.h"
#include "State.h"
#include "MenuState.h"
#include "GameState.h"

StateManager::StateManager(std::shared_ptr<Game> in) : instance(in) {
	std::shared_ptr<MenuState> menu = std::make_shared<MenuState>(std::shared_ptr<StateManager>(this));
	std::shared_ptr<GameState> game = std::make_shared<GameState>(std::shared_ptr<StateManager>(this));
	addState(static_pointer_cast<State, MenuState>(menu));
	addState(static_pointer_cast<State, GameState>(game));
}

StateManager::~StateManager() {

}

void StateManager::addState(std::shared_ptr<State> state) {

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
		throw exception();
#endif
	}
}

void StateManager::tick(std::shared_ptr<InputHandle>& input) {
	current->tick(input);
}

void StateManager::draw(std::shared_ptr<Renderer>& renderer) {
	current->draw(renderer);
}