#pragma once
#include "PolygonBody.h"

class PhysicsEngine;
class Composite;

class PhysicsBody :
	public Drawable
{
public:
	PhysicsBody();

	virtual Vector2f getVelocity();
	virtual float getFriction();
	virtual float getMass();
	virtual float getInvMass();
	virtual Vector2f getForce();
	virtual bool isActive();

	//construct a quadrangle with the given dimensions, and translate to the given position
	//the position supplied will be the top left position after translation
	virtual void constructQuad(const Vector2f &position, const Vector2f& dimensions);

	//construct a polygon with direct pixel coordinates, performs no translations
	//does not check that the polygon is convex(which is required)
	virtual void constructPoly(const vector<Vector2f> &points);

	//creates a polygon that is scaled and translated to fit in the quad bounds
	//the points must range from 0 to 1 (openGL style)
	virtual void constructPoly(const vector<Vector2f> &points0_to_1, const FloatRect &quadbounds);

	//set the transform of this object
	//to be the centroid of the body
	Vector2f getCentroid() const;

	Composite* getParent();

	PolygonBody getBody();

	vector<PhysicsBody*> neighbors;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual int getType() = 0;

	Vector2f getMin();
	Vector2f getMax();

protected:

	friend class Composite;

	PolygonBody body;

	Composite* parent;

	float friction = 0.2f;

	//used only by composite
	virtual void translate(const Vector2f &trans);

	virtual void setVelocity(Vector2f newVel);
	virtual void addVelocity(Vector2f v);
	virtual void setMass(float m);
	virtual void setDensity(float density);
	virtual void setFriction(float f);
	virtual void addForce(Vector2f f);
	virtual void setForce(Vector2f f);
	virtual void setActive(bool a);
	virtual void Register(PhysicsEngine* engine) = 0;
};

