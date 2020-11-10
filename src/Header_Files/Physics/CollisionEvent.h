#pragma once
#include <array>
#include <memory>

class PhysicsBody;

//CollisionEvent.h
/*
  object for communicating information about collisions that have occured
*/
class CollisionEvent
{
public:
	CollisionEvent(PhysicsBody* A, const size_t ABodyNum,
		PhysicsBody* B, const size_t BBodyNum, const s2d::NormalVec& normal,
		const float seperation,
		const std::array<s2d::Point, 2>& contactPoints);

	PhysicsBody* A;
	PhysicsBody* B;

	s2d::NormalVec normal;
	float seperation;
	std::array<s2d::Point, 2> contactPoints;
};

