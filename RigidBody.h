#pragma once
#include "PhysicsBody.h"

class RigidBody :
	public PhysicsBody
{

public:

	RigidBody();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Vector2f getVelocity();
	virtual void setVelocity(Vector2f newVel);
	virtual void setMass(float m);
	virtual void setDensity(float density);
	virtual void addVelocity(Vector2f v);
	virtual void addForce(Vector2f f);

	virtual float getMass();
	virtual float getInvMass();

	virtual void setForce(Vector2f f);
	virtual Vector2f getForce();

	virtual void setActive(bool a);
	virtual bool isActive();
	virtual void Register(PhysicsEngine* engine);

	virtual int getType() {
		return 0;
	}

private:

	void translate(const Vector2f &trans);

	//body properties
	Vector2f vel = Z_VEC;
	Vector2f force = Z_VEC;
	float mass = 0;
	float massinv = 0;

	//variables used to track the sleeping state
	int sleeptimer = 0;
	const int maxsleep = 0;
	const float tolerence = 0.1;
	bool active = true;

};
