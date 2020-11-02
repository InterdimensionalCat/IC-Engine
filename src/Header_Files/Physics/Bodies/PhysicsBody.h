#pragma once
#include "Behavior.h"
#include "Space2D.h"

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

	s2d::GameUnits::Vec getVelocity() const;
	float getFriction() const;
	float getMass() const;
	float getInvMass() const;
	s2d::GameUnits::Vec getForce() const;
	bool isAwake() const;
	bool isStatic() const;
	void setEdgeActive(const size_t bodyNum, const size_t edgeNum, const bool active);
	bool isEdgeActive(const size_t bodyNum, const size_t edgeNum) const;
	CollisionType getType() const;
	void setType(const CollisionType type);

	const std::vector<s2d::GameUnits::Poly>& getBodies() const;
	void addPoly(const s2d::GameUnits::Poly &toAdd, const bool activeSet = true);
	s2d::GameUnits::Poly getBody(const size_t bodyNum = 0);
	std::vector<PhysicsBody*>& getNeighbors();

	void translate(const s2d::GameUnits::Vec& trans);
	void setVelocity(const s2d::GameUnits::Vec& velocity);
	void addVelocity(const s2d::GameUnits::Vec& velocity);
	void setMass(const float mass);
	void setDensity(const float density);
	void setFriction(const float friction);
	void addForce(const s2d::GameUnits::Vec &force);
	void setForce(const s2d::GameUnits::Vec &force);
	void setAwake(const bool a);
	PhysEventHandler* getInfo();

	s2d::GameUnits::Point getMinBound() const;
	s2d::GameUnits::Point getMaxBound() const;

	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);


protected:

	friend class PhysicsEngine;

	float friction = 0.2f;
	float mass;
	float massinv;

	s2d::GameUnits::Vec v;

	s2d::GameUnits::Vec force;
	s2d::GameUnits::Vec velocity;

	bool awake = true;
	int sleeptimer = 0;
	const int maxsleep = 0;
	const float tolerence = 0.1f;

	PhysicsEngine* engine;
	GameTransform* transform;
	PhysEventHandler* collisioninfo;

	std::vector<s2d::GameUnits::Poly> bodies;
	//each edge of each body maps to a bool value in the same position to determine whether or not its "active"
	std::vector<std::vector<bool>> activeEdges;

	std::vector<PhysicsBody*> neighbors;

	CollisionType type;
};

