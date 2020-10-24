#pragma once
#include "PolygonBody.h"

class PhysicsBody;
class Edge;

//object for communicating information about collisions that have occured
class CollisionEvent
{
public:
	CollisionEvent(PhysicsBody* A, PhysicsBody* B, const Vector2f normal, const float seperation, const Edge contactEdge);
	PhysicsBody* A;
	PhysicsBody* B;

	Vector2f normal;
	float seperation;
	Edge contactEdge;
};

