#include "include.h"
#include "Composite.h"
#include "PhysicsBody.h"
#include "GameTransform.h"
#include "Actor.h"
#include "SweepAndPrune.h"
#include "PhysicsEngine.h"


Composite::Composite() {

}

void Composite::addBody(PhysicsBody* body) {
	bodies.push_back(std::move(shared_ptr<PhysicsBody>(body)));
	body->parent = this;
}

void Composite::generate() {

	//disable edges
	for (size_t i = 0; i < bodies.size(); i++) {
		auto &b1 = bodies.at(i);
		size_t j = i < bodies.size() - 1 ? i + 1 : 0;
		for (; j < bodies.size(); j++) {
			auto &b2 = bodies.at(j);
			if (b1 != b2) {
				for (auto &e1 : b1->body.edges) {
					for (auto &e2 : b2->body.edges) {
						if ((e1.start == e2.start || e1.start == e2.end) &&
							(e1.end == e2.start || e1.end == e2.end)) {
							e1.active = false;
							e2.active = false;
						}
					}
				}
			}
		}

	}
}

void Composite::translate(const Vector2f &trans) {

	for (auto& b : bodies) {
		b->translate(trans);
	}
	transform->translate(trans);
	possync = transform->getPos();
}

void Composite::setVelocity(Vector2f newVel) {
	for (auto& b : bodies) {
		b->setVelocity(newVel);
	}
}

void Composite::addVelocity(Vector2f v) {
	for (auto& b : bodies) {
		b->addVelocity(v);
	}
}

void Composite::setMass(float m) {
	for (auto& b : bodies) {
		b->setMass(m);
	}
}

void Composite::setDensity(float density) {
	for (auto& b : bodies) {
		b->setDensity(density);
	}
}

void Composite::setFriction(float f) {
	for (auto& b : bodies) {
		b->setFriction(f);
	}
}

void Composite::addForce(Vector2f f) {
	for (auto& b : bodies) {
		b->addForce(f);
	}
}

void Composite::setForce(Vector2f f) {
	for (auto& b : bodies) {
		b->setForce(f);
	}
}

void Composite::setActive(bool a) {
	for (auto& b : bodies) {
		b->setActive(a);
	}
}

void Composite::start() {
	transform = this->getActor()->getBehavior<GameTransform>();
	possync = transform->getPos();
}

void Composite::tick(InputHandle* input) {

	//ensure that the postion is always sync'd to the transform
	if (possync != transform->getPos()) {
		this->translate(transform->getPos() - possync);
	}
}

void Composite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& b : bodies) {
		b->draw(target, states);
	}
}

Vector2f Composite::getVelocity() {
	return bodies.at(0)->getVelocity();
}

float Composite::getFriction() {
	return bodies.at(0)->getFriction();
}

float Composite::getMass() {
	return bodies.at(0)->getMass();
}

float Composite::getInvMass() {
	return bodies.at(0)->getInvMass();
}

Vector2f Composite::getForce() {
	return bodies.at(0)->getForce();
}

bool Composite::isActive() {
	return bodies.at(0)->isActive();
}

void Composite::clearNeighbors() {
	for (auto& body : bodies) {
		body->neighbors.clear();
	}
}

void Composite::Register(PhysicsEngine* engine) {
	engine->addComposite(this);
	for (auto& b : bodies) {
		b->Register(engine);
	}
	this->generate();
}