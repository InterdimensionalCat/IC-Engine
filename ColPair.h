#pragma once
#include "PolygonBody.h"

class PhysicsBody;
class RigidBody;
class StaticBody;


//key used to search the map of collisions
struct PairKey {
	PairKey(PhysicsBody* A, PhysicsBody* B) {
		if (A < B) {
			bmin = A;
			bmax = B;
		}
		else {
			bmin = B;
			bmax = A;
		}
	}

	PhysicsBody* bmin;
	PhysicsBody* bmax;
};

//data structure used for collisiosn
//contains both rigid bodies involved in the collsion
//as well as the MTV angle and magnitude
struct ColPair :
	public Drawable
{
public:
	//construct a collisionPair with the two potentially
	//colliding bodies
	ColPair(PhysicsBody* A, PhysicsBody* B);

	//the two objects in question
	PhysicsBody* A;
	PhysicsBody* B;

	//test if two colPairs are duplicates;
	bool operator==(const ColPair &other);

	//perform pre-calculations
	void preUpdate(float invDT);

	//resolve collision
	void solveCollision();

	Vector2f normal;
	float seperation;
	Edge contactEdge;

	//accumulated impulse and position updates
	float accImp = 0.0f;
	float accPos = 0.0f;
	float accTan = 0.0f;

	//precalculated variables
	float normalMass;
	float tangentMass;
	float bias;
	float friction;

	//true if a collision occured
	bool valid;

	void update(const ColPair& other);

	//for debugging purposes
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

bool RigidPairSAT(ColPair &pair);
bool RigidStaticSAT(ColPair &pair);
bool RigidOneWaySAT(ColPair &pair);
bool dummySAT(ColPair &pair);