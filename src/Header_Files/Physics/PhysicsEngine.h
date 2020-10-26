#pragma once
#include <map>
#include "ColPair.h"
#include "SweepAndPrune.h"
#include "collisionEvent.h"

class PhysicsBody;
class RigidBody;
class StaticBody;
class Composite;

//physics engine is a singleton

//physics units: meters, physics grid:
//        y+
//    x-      x+
//        y-
class PhysicsEngine
{
public:


	PhysicsEngine();

	//destructor


	void updatePhysics(double deltaTime);

	void addBody(RigidBody* b);
	void addBody(StaticBody* b);

	void addComposite(Composite* comp);
	void generateComposite(Composite* ptr);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	//updates the intervals of all rigid bodies for the purposes
	//of the sweep and prune algorithm
	void updateSweeper();

private:

	friend class CollisionEvent;
	friend class Level;

	void sweepAndPrune();

	//Move all objects according to the forces they have
	void moveBodies(float dt);

	//integretes forces in each body
	void integrateForce(float dt);


	vector<RigidBody*> bodies;
	vector<StaticBody*> statics;


	vector<Composite*> composites;

	//container storing all generated possible collisions on a particular
	//physics update
	map<PairKey, ColPair> collisions;

	//gravity vector
	//gravity is typically 10 meters per second squared
	Vector2f gravity;

	//number of times the engine resolves collisions in a frame
	int iterations;

	//sweep and prune container
	SweepAndPrune sweeper;

};

//necessasary for the map to function
inline bool operator<(const PairKey &lhs, const PairKey &rhs) {
	if (lhs.bmin < rhs.bmin) {
		return true;
	}

	if (lhs.bmin == rhs.bmin && lhs.bmax < rhs.bmax) {
		return true;
	}

	return false;
}

void set(PhysicsEngine* engine);