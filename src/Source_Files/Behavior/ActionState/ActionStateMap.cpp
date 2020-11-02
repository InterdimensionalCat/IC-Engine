#include "include.h"
#include "ActionStateMap.h"
#include "ActionState.h"
#include "Actor.h"
#include "GameTransform.h"
#include "Animator.h"
#include "PhysicsBody.h"
#include "PhysEventHandler.h"



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
#ifdef _DEBUG
		cerr << "Action State " << key << " does not exist!\n";
		throw exception();
#endif
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

void ActionStateMap::tick(InputHandle* input) {
	current->run(input);
}

void ActionStateMap::draw(Renderer* renderer) {
	current->draw(renderer);
}