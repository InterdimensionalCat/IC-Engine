#include "include.h"
#include "PhysicsEngine.h"
#include "PhysicsBody.h"
#include "SweepAndPrune.h"
#include "ColPair.h"
#include "PhysMath.h"
#include "SweepAndPrune.h"
#include "CollisionEvent.h"
#include "PhysEventHandler.h"
#include "GameTransform.h"


using namespace s2d;


PhysicsEngine::PhysicsEngine() : gravity(Vec(0.0f, 600.0f)), iterations(10) {}

void PhysicsEngine::updatePhysics(const float deltaTime) {

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

	for (std::shared_ptr<PhysicsBody>& body : bodies) {
		if (body->collisioninfo.get() != nullptr) {
			body->collisioninfo->events.clear();
		}
	}

	auto &intervals = sweeper.bodies;

	vector<SweepEntry> activeIntervals;


	for (size_t i = 0; i < intervals.size(); i++) {

		auto &entry = intervals[i];

		activeIntervals.erase(std::remove_if(activeIntervals.begin(), activeIntervals.end(),
			[&entry](const SweepEntry &x) {return x.interval.max < entry.interval.min; }), activeIntervals.end());

			for (auto &entry2 : activeIntervals) {

				auto b1 = entry.body;
				auto b2 = entry2.body;

				if (b1 == b2) continue;

				PairKey key(b1, b2);
				ColPair pair(b1, entry.polyInd, b2, entry2.polyInd);
				if (pair.valid) {
					pair.A->getNeighbors().push_back(pair.B);
					pair.B->getNeighbors().push_back(pair.A);
					collisions.emplace(key, pair);
				}
			}

			activeIntervals.push_back(entry);

	}
}

void PhysicsEngine::moveBodies(float dt) {

	for (auto b : bodies) {
		b->translate(b->getVelocity() * dt);
		b->setForce(Vec());
		if (b->isAwake()) {
			b->getNeighbors().clear();
		}
	}
}

void PhysicsEngine::integrateForce(const float dt) {
	for (auto &b : bodies) {
		if (b->getMass() == 0) continue;
		b->addVelocity((gravity +  b->getForce() * b->getInvMass()) * dt);
	}
}

void PhysicsEngine::addBody(std::shared_ptr<PhysicsBody> b) {
	bodies.push_back(b);
	auto size = bodies.size();
	auto polySize = b->getBodies().size();
	for (size_t i = 0; i < polySize; i++) {
		sweeper.addBody(bodies[size - 1], i);
	}
}


