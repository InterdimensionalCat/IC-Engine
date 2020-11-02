#pragma once
#include <array>

class PhysicsBody;


//object for communicating information about collisions that have occured
class CollisionEvent
{
public:
	CollisionEvent(PhysicsBody* A, const size_t ABodyNum,
		PhysicsBody* B, const size_t BBodyNum, const s2d::GameUnits::Normal_Vec& normal,
		const float seperation,
		const std::array<s2d::GameUnits::Point, 2>& contactPoints);

	PhysicsBody* A;
	PhysicsBody* B;

	s2d::GameUnits::Normal_Vec normal;
	float seperation;
	std::array<s2d::GameUnits::Point, 2> contactPoints;
};

