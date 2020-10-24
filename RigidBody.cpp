#include "include.h"
#include "RigidBody.h"
#include "Actor.h"
#include"PhysicsEngine.h"


RigidBody::RigidBody() {

}

Vector2f RigidBody::getVelocity() {
	return vel;
}

void RigidBody::setVelocity(Vector2f newVel) {
	vel = newVel;
}

void RigidBody::translate(const Vector2f &trans) {
	if (!active && VecLen(trans)) {
		vel = Z_VEC;
		return;
	}
	if (VecLen(trans) < tolerence) {
		sleeptimer++;
		if (sleeptimer > maxsleep && neighbors.size() > 0) {
			//SET SO THAT AN OBJECT MUST BE COLLIDING WITH
			//ANOTHER OBJECT TO BE PUT TO SLEEP
			active = false;
			sleeptimer = 0;
			return;
		}
	}
	else {
		sleeptimer = 0;
	}

	body.translate(trans);
}

void RigidBody::setMass(float m) {
	mass = m;
	if (mass == 0) {
		massinv = 0;
	}
	else {
		massinv = 1 / m;
	}
}

void RigidBody::setDensity(float density) {
	mass = body.area() * density;
	if (mass == 0) {
		massinv = 0;
		return;
	}
	massinv = 1 / mass;
}

void RigidBody::addVelocity(Vector2f v) {
	active = true;
	vel += v;
}

void RigidBody::addForce(Vector2f f) {
	active = true;
	force += f;
}

float RigidBody::getMass() {
	return mass;
}

float RigidBody::getInvMass() {
	return massinv;
}

void RigidBody::setForce(Vector2f f) {
	force = f;
}

Vector2f RigidBody::getForce() {
	return force;
}

void RigidBody::setActive(bool a) {
	active = a;
}

bool RigidBody::isActive() {
	return active;
}

void RigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//polygon draw

	ConvexShape drawshape;
	drawshape.setPointCount(body.edges.size());
	for (size_t i = 0; i < body.edges.size(); i++) {
		drawshape.setPoint(i, body.edges.at(i).start);
	}
	//drawshape.setOrigin(pos);
	drawshape.setOutlineColor(Color::Red);
	drawshape.setFillColor(Color::Transparent);
	drawshape.setOutlineThickness(3);
	target.draw(drawshape, states);

	//draw normals


	for (size_t i = 0; i < body.edges.size(); i++) {

		VertexArray line(Lines, 2);

		Vector2f midp = body.edges.at(i).end - body.edges.at(i).start;
		midp = Vector2f(midp.x / 2.0f, midp.y / 2.0f) + body.edges.at(i).start;
		line[0] = midp;
		line[1] = midp + body.edges.at(i).normal * 0.3f;

		if (body.edges.at(i).active) {
			line[0].color = Color::Yellow;
			line[1].color = Color::Yellow;
		}
		else {
			line[0].color = Color::Black;
			line[1].color = Color::Black;
		}

		target.draw(line, states);
	}

	//draw center

	float radius = 0.5;

	CircleShape drawS;
	Vector2f cent = this->getCentroid();
	drawS.setPosition(Vector2f(cent.x, cent.y));
	drawS.setRadius(radius);
	drawS.setOutlineColor(Color::Yellow);
	drawS.setFillColor(Color::Yellow);
	drawS.setOutlineThickness(3);
	target.draw(drawS, states);
}

void RigidBody::Register(PhysicsEngine* engine) {
	engine->addBody(this);
}