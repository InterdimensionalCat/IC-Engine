#pragma once
#include "Behavior.h"
#include "CollisionEvent.h"

class PhysicsBody;
class GameTransform;
class SweepAndPrune;
class PhysicsEngine;
class CollisionEvent;

class Composite :
	public Behavior
{
public:
	Composite();
	void addBody(PhysicsBody* body);
	void generate();


	void translate(const Vector2f &trans);
	void setVelocity(Vector2f newVel);
	void addVelocity(Vector2f v);
	void setMass(float m);
	void setDensity(float density);
	void setFriction(float f);
	void addForce(Vector2f f);
	void setForce(Vector2f f);
	void setActive(bool a);
	void Register(PhysicsEngine* engine);

	Vector2f getVelocity();
	float getFriction();
	float getMass();
	float getInvMass();
	Vector2f getForce();
	bool isActive();
	void clearNeighbors();

	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool updated = false;

	vector<CollisionEvent> collisionInfo;

private:
	vector<shared_ptr<PhysicsBody>> bodies;
	GameTransform* transform;
	Vector2f possync;
};

