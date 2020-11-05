#include "include.h"
#include "ActionStateMap.h"
#include "ActionState.h"
#include "Actor.h"
#include "GameTransform.h"
#include "Animator.h"
#include "PhysicsBody.h"
#include "PhysEventHandler.h"



void ActionStateMap::addState(std::shared_ptr<ActionState>& state) {

	map.emplace(state->getName(), state);
	state->parent = std::shared_ptr<ActionStateMap>(this);
	state->init();
	if (current.get() == nullptr) {
		current = map.at(state->getName());
		current->enter();
	}
}

void ActionStateMap::setState(const string &key, shared_ptr<InputHandle>& input) {
	if (map.find(key) != map.end()) {
		if (current.get() != nullptr) {
			current->exit();
		}
		current = map.at(key);
		current->enter();
		current->run(input);
	}
	else {
#ifdef _DEBUG
		cerr << "Action State " << key << " does not exist!\n";
		throw exception();
#endif
	}
}

void ActionStateMap::setState(const string &key) {
	if (map.find(key) != map.end()) {
		if (current.get() != nullptr) {
			current->exit();
		}
		current = map.at(key);
		current->enter();
	}
	else {
#ifdef _DEBUG
		cerr << "Action State " << key << " does not exist!\n";
		throw exception();
#endif
	}
}

void ActionStateMap::start() {
	animator = getActor()->getBehavior<Animator>();
	transform = getActor()->getBehavior<GameTransform>();
	body = getActor()->getBehavior<PhysicsBody>();
	collisioninfo = getActor()->getBehavior<PhysEventHandler>();
}

void ActionStateMap::tick(std::shared_ptr<InputHandle>& input) {
	current->run(input);
}

void ActionStateMap::draw(std::shared_ptr<Renderer>& renderer) {
	current->draw(renderer);
}