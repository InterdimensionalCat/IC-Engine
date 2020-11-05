#include "include.h"
#include "Actor.h"
#include "Behavior.h"
#include "Level.h"

void Actor::start() {
	for (auto &c : components) {
		c->start();
	}
}

void Actor::tick(std::shared_ptr<InputHandle>& input) {
	for (auto &c : components) {
		c->tick(input);
	}
}

void Actor::draw(std::shared_ptr<Renderer>& renderer) {
	for (auto &c : components) {
		c->draw(renderer);
	}
}

bool Actor::compareTag(const std::shared_ptr<Actor>& other) const {
	return getTag() == other->getTag();
}