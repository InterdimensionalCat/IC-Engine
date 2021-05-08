#include "include.h"
#include "Actor.h"
#include "Behavior.h"
#include "Level.h"

void Actor::start() {
	for (auto &c : components) {
		c->start();
	}
}

void Actor::tick(InputHandle* input) {
	for (auto &c : components) {
		c->tick(input);
	}
}

void Actor::draw(Renderer* renderer) {
	for (auto &c : components) {
		c->draw(renderer);
	}
}

bool Actor::compareTag(const Actor* other) const {
	return getTag() == other->getTag();
}