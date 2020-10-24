#include "include.h"
#include "PhysicsEngine.h"
#include "PhysicsBody.h"
#include "SweepAndPrune.h"
#include "ColPair.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "PhysMath.h"
#include "SweepAndPrune.h"
#include "CollisionEvent.h"
#include "Composite.h"

PhysicsEngine* physicsengine = nullptr;

void set(PhysicsEngine* engine) {
	physicsengine = engine;
}


PhysicsEngine::PhysicsEngine() : gravity(Vector2f(0.0f, -10.0f)), iterations(10) {}


void PhysicsEngine::updateSweeper() {
	for (RigidBody* b : bodies) {
		sweeper.updateBody(b);
	}

	for (StaticBody* b : statics) {
		sweeper.updateBody(b);
	}
}

void PhysicsEngine::updatePhysics(double deltaTime) {

	float invDT = deltaTime > 0 ? 1.0f / (float)deltaTime : 0.0f;

	//generate possible collisions using broad phase
	sweepAndPrune();

	//integrate forces
	integrateForce((float)deltaTime);

	//perform pre calculations
	for (auto it = collisions.begin(); it != collisions.end(); it++) {
		it->second.preUpdate(invDT);
	}

	//solve collisions iteratively
	for (int i = 0; i < iterations; i++) {
		for (auto it = collisions.begin(); it != collisions.end(); it++) {
			it->second.solveCollision();
		}
	}

	//integrate velocities
	moveBodies((float)deltaTime);
}

void PhysicsEngine::sweepAndPrune() {
	collisions.clear();
	sweeper.sort();

	auto &intervals = sweeper.bodies;

	vector<pair<SweepInterval, PhysicsBody*>> activeIntervals;


	for (int i = 0; i < intervals.size(); i++) {

		auto &pair = intervals.at(i);

		activeIntervals.erase(std::remove_if(activeIntervals.begin(), activeIntervals.end(),
			[&pair](const std::pair<SweepInterval, PhysicsBody*> &x) {return x.first.max < pair.first.min; }), activeIntervals.end());

			for (auto &pair2 : activeIntervals) {

				auto b1 = pair.second;
				auto b2 = pair2.second;

				if (b1->getParent() == b2->getParent() && b1->getParent() != nullptr) {
					continue;
				}

				PairKey key((PhysicsBody*)b1, (PhysicsBody*)b2);
				ColPair pair(b1, b2);
				if (pair.valid) {
					pair.A->neighbors.push_back(pair.B);
					pair.B->neighbors.push_back(pair.A);
					collisions.emplace(key, pair);
				}
			}

			activeIntervals.push_back(pair);

	}
}

void PhysicsEngine::moveBodies(float dt) {

	for (Composite* comp : composites) {
		comp->updated = false;
	}

	for (RigidBody* b : bodies) {
		Composite* comp = b->getParent();
		if (comp->updated) continue;
		comp->updated = true;
		comp->translate(dt * comp->getVelocity());
		comp->setForce(Z_VEC);
		if (comp->isActive()) {
			comp->clearNeighbors();
		}

		if (comp->getVelocity() != Z_VEC) {
			sweeper.updateBody(b);
		}
	}
}

void PhysicsEngine::integrateForce(float dt) {
	for (Composite* comp : composites) {
		comp->updated = false;
	}


	for (auto &b : bodies) {

		Composite* comp = b->getParent();
		if (comp->updated) continue;
		comp->updated = true;

		if (comp->getMass() == 0.0f) continue;
		comp->addVelocity(dt * (gravity + comp->getInvMass() * comp->getForce()));
	}
}

void PhysicsEngine::addBody(RigidBody* b) {
	bodies.push_back(b);
	sweeper.updateBody(bodies.at(bodies.size() - 1));
}

void PhysicsEngine::addBody(StaticBody* b) {
	statics.push_back(b);
	sweeper.updateBody(statics.at(statics.size() - 1));
}

void PhysicsEngine::addComposite(Composite* comp) {
	composites.push_back(comp);
}

void PhysicsEngine::generateComposite(Composite* ptr) {
	ptr->generate();

	for (RigidBody* body : bodies) {
		sweeper.updateBody(body);
	}

	for (StaticBody* body : statics) {
		sweeper.updateBody(body);
	}
}

void PhysicsEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (instance->debug) {

		//draw the sweep and prune intervals
		auto intervals = sweeper.bodies;
		for (auto &pair : intervals) {
			VertexArray line(Lines, 2);
			

			line[0] = Vector2f(pair.first.min, 0);
			line[1] = Vector2f(pair.first.min, instance->HEIGHT);

			line[0].color = Color::Green;
			line[1].color = Color::Green;

			target.draw(line, states);

			line[0] = Vector2f(pair.first.max, 0);
			line[1] = Vector2f(pair.first.max, instance->HEIGHT);

			line[0].color = Color::Blue;
			line[1].color = Color::Blue;

			target.draw(line, states);
		}

		//draw collisions
		for (auto &p : collisions) {
			target.draw(p.second, states);
		}
	}
}


