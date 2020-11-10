#pragma once
#include "Behavior.h"
#include "Space2D.h"

//PhysicsBody.h
/*
  Behavior that puts its actor in the physics engine, physics bodies are comprised of 
  1 or more polygon bodies and will simulate non-rotating rigid bodies. THIS BEHAVIOR TAKES
  CONTROL OF THE GAMETRANSFORM so do not move actors that have this object through te game transform
  unless you want to teleport them
*/

class PhysicsEngine;
class GameTransform;
class PhysEventHandler;

enum class CollisionType {
	Dynamic = 0,
	Static = 1,
	OneWay = 2
};

class PhysicsBody :
	public Behavior
{
public:

	//getters for various properties of the body
	s2d::Vec getVelocity() const;
	float getFriction() const;
	float getMass() const;
	float getInvMass() const;
	s2d::Vec getForce() const;

	//check if this body is currently being updated by the engine. 
	//Objects at rest for an extended period of time will stop recieving updates
	//until another object interracts with them
	bool isAwake() const;

	bool isStatic() const;

	//Sets and checks active edges; an inactive edge will not be selected as the axis of collision
	//When two objects collide, so edges that cannot be hit should be set as inactive
	void setEdgeActive(const size_t bodyNum, const size_t edgeNum, const bool active);
	bool isEdgeActive(const size_t bodyNum, const size_t edgeNum) const;

	//Sets and checks the type of the physics body,
	CollisionType getType() const;
	void setType(const CollisionType type);

	//functions that manipulate the polygon bodies that make up the physics body
	const std::vector<s2d::Poly>& getBodies() const;
	void addPoly(const s2d::Poly &toAdd, const bool activeSet = true);
	s2d::Poly getBody(const size_t bodyNum = 0);

	//gets the neighbors of this body,  neighbors are bodies that are touching, and when one
	//becomes active from a collision, all its neighbors also become active
	std::vector<PhysicsBody*>& getNeighbors();

	void translate(const s2d::Vec& trans);
	void setVelocity(const s2d::Vec& velocity);
	void addVelocity(const s2d::Vec& velocity);
	void setMass(const float mass);
	void setDensity(const float density);
	void setFriction(const float friction);
	void addForce(const s2d::Vec &force);
	void setForce(const s2d::Vec &force);
	void setAwake(const bool a);

	PhysEventHandler* getInfo();


	//the min an max bound are the two points that make up
	//a bounding box around the polygon
	s2d::Point getMinBound() const;
	s2d::Point getMaxBound() const;

	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);


protected:

	//friend class PhysicsEngine;

	float friction = 0.2f;
	float mass = 0.0f;
	float massinv = 0.0f;

	s2d::Vec force;
	s2d::Vec velocity;

	bool awake = true;
	int sleeptimer = 0;
	const int maxsleep = 0;
	const float tolerence = 0.1f;// * 60.0f;

	PhysicsEngine* engine;
	GameTransform* transform;
	PhysEventHandler* collisioninfo;

	std::vector<s2d::Poly> bodies;
	//each edge of each body maps to a bool value in the same position to determine whether or not its "active"
	std::vector<std::vector<bool>> activeEdges;

	std::vector<PhysicsBody*> neighbors;

	CollisionType type;
};

