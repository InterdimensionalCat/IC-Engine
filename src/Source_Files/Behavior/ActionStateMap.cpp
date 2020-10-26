#include "include.h"
#include "ActionStateMap.h"
#include "ActionState.h"



void ActionStateMap::addState(ActionState* state) {

	map.emplace(state->getName(), shared_ptr<ActionState>(state));
	state->parent = this;
	state->init();
	if (current == nullptr) {
		current = map.at(state->getName()).get();
		current->enter();
	}
}

void ActionStateMap::setState(const string &key, InputHandle* input) {
	if (map.find(key) != map.end()) {
		if (current != nullptr) {
			current->exit();
		}
		current = map.at(key).get();
		current->enter();
		current->run(input);
	}
	else {
		cerr << "Action State " << key << " does not exist!\n";
	}
}

void ActionStateMap::setState(const string &key) {
	if (map.find(key) != map.end()) {
		if (current != nullptr) {
			current->exit();
		}
		current = map.at(key).get();
		current->enter();
	}
	else {
		cerr << "Action State " << key << " does not exist!\n";
	}
}

void ActionStateMap::start() {

}

void ActionStateMap::tick(InputHandle* input) {
	current->run(input);
}

void ActionStateMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*current, states);
}