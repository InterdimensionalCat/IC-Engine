#include "include.h"
#include "PhysicsBody.h"
#include "PhysicsEngine.h"
#include "GameTransform.h"
#include "PolygonBody.h"
#include "Composite.h"

PhysicsBody::PhysicsBody() {}


Vector2f PhysicsBody::getVelocity() {
	return Z_VEC;
}

void PhysicsBody::setVelocity(Vector2f newVel) {}

void PhysicsBody::setMass(float m) {}

void PhysicsBody::setDensity(float density) {}

void PhysicsBody::addVelocity(Vector2f v) {}

void PhysicsBody::setFriction(float f) {
	friction = f;
}

void PhysicsBody::addForce(Vector2f f) {}

float PhysicsBody::getFriction() {
	return friction;
}

float PhysicsBody::getMass() {
	return 0;
}

float PhysicsBody::getInvMass() {
	return 0;
}

void PhysicsBody::translate(const Vector2f &trans) {
	body.translate(trans);

}

void PhysicsBody::constructQuad(const Vector2f& position, const Vector2f& dimensions) {
	body = PolygonBody();
	body.edges.resize(4);
	body.edges.at(0) = Edge(position, position + Vector2f(dimensions.x, 0));
	body.edges.at(1) = Edge(position + Vector2f(dimensions.x, 0), position + dimensions);
	body.edges.at(2) = Edge(position + dimensions, position + Vector2f(0, dimensions.y));
	body.edges.at(3) = Edge(position + Vector2f(0, dimensions.y), position);
}

void PhysicsBody::constructPoly(const vector<Vector2f> &points) {
	body = PolygonBody();
	body.edges.resize(points.size());
	for (int stpt = 0; stpt < points.size(); stpt++) {
		int edpt = stpt + 1 < points.size() ? stpt + 1 : 0;
		body.edges.at(stpt) = Edge(points.at(stpt), points.at(edpt));
	}
}

void PhysicsBody::constructPoly(const vector<Vector2f> &points0_to_1, const FloatRect &quadbounds) {
	float xmin = quadbounds.left;
	float ymin = quadbounds.top;

	float xmax = quadbounds.left + quadbounds.width;
	float ymax = quadbounds.top + quadbounds.height;

	vector<Vector2f> points(points0_to_1.size());
	for (int i = 0; i < points0_to_1.size(); i++) {
		//interpolate between the bounds for both the x and y coordinate
		points.at(i) = Vector2f(lerp(xmin, xmax, points0_to_1.at(i).x), lerp(ymin, ymax, points0_to_1.at(i).y));
	}

	body = PolygonBody();
	body.edges.resize(points.size());
	for (int stpt = 0; stpt < points.size(); stpt++) {
		int edpt = stpt + 1 < points.size() ? stpt + 1 : 0;
		body.edges.at(stpt) = Edge(points.at(stpt), points.at(edpt));
	}
}


Vector2f PhysicsBody::getCentroid() const {

	Vector2f newpos = Z_VEC;

	float signedArea = 0;
	int n = body.edges.size();
	// For all vertices 
	for (int i = 0; i < body.edges.size(); i++) {

		Vector2f p0 = body.edges.at(i).start;
		Vector2f p1 = body.edges.at(i).end;

		// Calculate value of A 
		// using shoelace formula 
		float A = (p0.x * p1.y) - (p1.x * p0.y);
		signedArea += A;

		// Calculating coordinates of 
		// centroid of polygon 
		newpos.x += (p0.x + p1.x) * A;
		newpos.y += (p0.y + p1.y) * A;
	}

	signedArea *= 0.5;
	newpos.x = (newpos.x) / (6 * signedArea);
	newpos.y = (newpos.y) / (6 * signedArea);

	return newpos;
}

Composite* PhysicsBody::getParent() {
	return parent;
}

void PhysicsBody::setForce(Vector2f f) {}

Vector2f PhysicsBody::getForce() {
	return Z_VEC;
}

void PhysicsBody::setActive(bool a) {}

bool PhysicsBody::isActive() {
	return false;
}

PolygonBody PhysicsBody::getBody() { 
	return body; 
}

Vector2f PhysicsBody::getMin() {

	Vector2f min(numeric_limits<float>::infinity(), numeric_limits<float>::infinity());

	for (auto &e : body.edges) {

		if (e.start.x < min.x) {
			min.x = e.start.x;
		}

		if (e.start.y < min.y) {
			min.y = e.start.y;
		}
	}


	if (min.x == numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(min.x);
#endif
	}

	if (min.y == numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(min.y);
#endif
	}

	return min;
}

Vector2f PhysicsBody::getMax() {

	Vector2f max(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());

	for (auto &e : body.edges) {
		if (e.start.x > max.x) {
			max.x = e.start.x;
		}

		if (e.start.y > max.y) {
			max.y = e.start.y;
		}

	}

	if (max.x == -numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(max.x);
#endif
	}

	if (max.y == -numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(max.y);
#endif
	}

	return max;
}
