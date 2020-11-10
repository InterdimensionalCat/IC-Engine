#include "include.h"
#include "PhysicsBody.h"
#include "PhysicsEngine.h"
#include "GameTransform.h"
#include "CollisionEvent.h"
#include "Actor.h"
#include "Level.h"
#include "PhysEventHandler.h"

using namespace s2d;

void PhysicsBody::translate(const Vec& trans) {
	if (type == CollisionType::Static) return;

	if (!isAwake() && trans.Mag()) {
		velocity = Vec();
		return;
	}
	if (trans.Mag() < tolerence) {
		sleeptimer++;
		if (sleeptimer > maxsleep && neighbors.size() > 0) {
			//SET SO THAT AN OBJECT MUST BE COLLIDING WITH
			//ANOTHER OBJECT TO BE PUT TO SLEEP
			setAwake(false);
			sleeptimer = 0;
			return;
		}
	}
	else {
		sleeptimer = 0;
	}

	transform->translate(trans);
	for (auto& b : bodies) {
		b += trans;
	}

	SweepAndPrune& parent = Behavior::getActor()->owner->engine->sweeper;
	for (size_t i = 0; i < bodies.size(); i++) {
		parent.updateBody(this, i);
	}
}

Vec PhysicsBody::getVelocity() const {
	return velocity;
}
float PhysicsBody::getFriction() const {
	return friction;
}
float PhysicsBody::getMass() const {
	return mass;
}
float PhysicsBody::getInvMass() const {
	return massinv;
}
Vec PhysicsBody::getForce() const {
	return force;
}

bool PhysicsBody::isAwake() const {
	return awake;
}
bool PhysicsBody::isStatic() const {
	return type == CollisionType::Static;
}

void PhysicsBody::setEdgeActive(const size_t bodyNum, const size_t edgeNum, const bool active) {
	activeEdges[bodyNum][edgeNum] = active;
}


bool PhysicsBody::isEdgeActive(const size_t bodyNum, const size_t edgeNum) const {
	return activeEdges[bodyNum][edgeNum];
}

CollisionType PhysicsBody::getType() const {
	return type;
}

void PhysicsBody::setType(const CollisionType type) {
	if (type == CollisionType::Static) {
		setMass(0.0f);
	}
	this->type = type;
}

const std::vector<Poly>& PhysicsBody::getBodies() const {
	return bodies;
}

void PhysicsBody::addPoly(const Poly &toAdd, const bool activeSet) {
	bodies.push_back(toAdd);
	vector<bool> newActive(toAdd.size(), activeSet);
	activeEdges.push_back(newActive);
}

Poly PhysicsBody::getBody(const size_t bodyNum) {
	return bodies[bodyNum];
}

std::vector<PhysicsBody*>& PhysicsBody::getNeighbors() {
	return neighbors;
}

void PhysicsBody::setVelocity(const Vec& velocity) {
	if (type == CollisionType::Static) {
		PhysicsBody::velocity = Vec();
		return;
	}
	PhysicsBody::velocity = velocity;
}
void PhysicsBody::addVelocity(const Vec& velocity) {
	if (type == CollisionType::Static) {
		PhysicsBody::velocity = Vec();
		return;
	}
	PhysicsBody::velocity += velocity;
}
void PhysicsBody::setMass(const float mass) {
	if (type == CollisionType::Static) {
		PhysicsBody::mass = 0.0f;
		massinv = 0.0f;
		return;
	}
	PhysicsBody::mass = mass;
	massinv = mass == 0 ? 0 : 1 / mass;
}

void PhysicsBody::setDensity(const float density) {
	mass = 0.0f;
	massinv = 0.0f;
	if (type == CollisionType::Static) {
		return;
	}
	for (auto& a : bodies) {
		mass += a.area();
	}
	mass *= density;
	massinv = mass == 0 ? 0 : 1 / mass;
}
void PhysicsBody::setFriction(const float friction) {
	PhysicsBody::friction = friction;
}

void PhysicsBody::addForce(const Vec& force) {
	if (type == CollisionType::Static) {
		PhysicsBody::force = Vec();
		return;
	}
	PhysicsBody::force += force;
}

void PhysicsBody::setForce(const Vec& force) {
	if (type == CollisionType::Static) {
		PhysicsBody::force = Vec();
		return;
	}
	PhysicsBody::force = force;
}

void PhysicsBody::setAwake(const bool a) {
	if (type == CollisionType::Dynamic) {
		awake = true;
	}
	else {
		awake = a;
	}
}


Point PhysicsBody::getMinBound() const {
	Point minBound = Point(numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
	for (auto& a : bodies) {
		auto aabb = a.getAABB();
		minBound.x = min(minBound.x, aabb.min.x);
		minBound.y = min(minBound.y, aabb.min.y);
	}
#ifdef _DEBUG
	if (minBound.x == numeric_limits<float>::infinity() ||
		minBound.y == numeric_limits<float>::infinity()) {
		throw BadInfinityException();
	}
#endif
	return minBound;
}

Point PhysicsBody::getMaxBound() const {
	Point maxBound = Point(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());
	for (auto& a : bodies) {
		auto aabb = a.getAABB();
		maxBound.x = max(maxBound.x, aabb.max.x);
		maxBound.y = max(maxBound.y, aabb.max.y);
	}
#ifdef _DEBUG
	if (maxBound.x == -numeric_limits<float>::infinity() ||
		maxBound.y == -numeric_limits<float>::infinity()) {
		throw BadInfinityException();
	}
#endif
	return maxBound;
}

void PhysicsBody::start() {
	transform = Behavior::getActor()->getBehavior<GameTransform>();
	engine = Behavior::getActor()->owner->engine.get();
	collisioninfo = Behavior::getActor()->getBehavior<PhysEventHandler>();
	engine->addBody(this);
}

PhysEventHandler* PhysicsBody::getInfo() {
	return collisioninfo;
}

void PhysicsBody::tick(InputHandle* input) {

}

void PhysicsBody::draw(Renderer* renderer) {
	if (instance->debug) {
		for (auto& b : bodies) {
			renderer->window->draw(b.getDrawableSFMLPolygon(1.0f, sf::Color(0,0,0,0), sf::Color(0, 0, 0, 255)), renderer->states);
		}
	}
}

