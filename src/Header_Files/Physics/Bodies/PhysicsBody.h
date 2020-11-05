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

	s2d::Vec getVelocity() const;
	float getFriction() const;
	float getMass() const;
	float getInvMass() const;
	s2d::Vec getForce() const;
	bool isAwake() const;
	bool isStatic() const;
	void setEdgeActive(const size_t bodyNum, const size_t edgeNum, const bool active);
	bool isEdgeActive(const size_t bodyNum, const size_t edgeNum) const;
	CollisionType getType() const;
	void setType(const CollisionType type);

	const std::vector<s2d::Poly>& getBodies() const;
	void addPoly(const s2d::Poly &toAdd, const bool activeSet = true);
	s2d::Poly getBody(const size_t bodyNum = 0);
	std::vector<std::shared_ptr<PhysicsBody>>& getNeighbors();

	void translate(const s2d::Vec& trans);
	void setVelocity(const s2d::Vec& velocity);
	void addVelocity(const s2d::Vec& velocity);
	void setMass(const float mass);
	void setDensity(const float density);
	void setFriction(const float friction);
	void addForce(const s2d::Vec &force);
	void setForce(const s2d::Vec &force);
	void setAwake(const bool a);
	std::shared_ptr<PhysEventHandler> getInfo();

	s2d::Point getMinBound() const;
	s2d::Point getMaxBound() const;

	virtual void start();
	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);


protected:

	friend class PhysicsEngine;

	float friction = 0.2f;
	float mass = 0.0f;
	float massinv = 0.0f;

	s2d::Vec v;

	s2d::Vec force;
	s2d::Vec velocity;

	bool awake = true;
	int sleeptimer = 0;
	const int maxsleep = 0;
	const float tolerence = 0.1f;// * 60.0f;

	std::shared_ptr<PhysicsEngine> engine;
	std::shared_ptr<GameTransform> transform;
	std::shared_ptr<PhysEventHandler> collisioninfo;

	std::vector<s2d::Poly> bodies;
	//each edge of each body maps to a bool value in the same position to determine whether or not its "active"
	std::vector<std::vector<bool>> activeEdges;

	std::vector<std::shared_ptr<PhysicsBody>> neighbors;

	CollisionType type;
};

