#include "include.h"
#include "Actor.h"
#include "Behavior.h"

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

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto &c : components) {
		target.draw(*c, states);
	}
}

bool Actor::compareTag(const Actor* other) const {
	return getTag() == other->getTag();
}