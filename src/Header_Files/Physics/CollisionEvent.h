#pragma once
#include <array>
#include <memory>

class PhysicsBody;


//object for communicating information about collisions that have occured
class CollisionEvent
{
public:
	CollisionEvent(std::shared_ptr<PhysicsBody> A, const size_t ABodyNum,
		std::shared_ptr<PhysicsBody> B, const size_t BBodyNum, const s2d::NormalVec& normal,
		const float seperation,
		const std::array<s2d::Point, 2>& contactPoints);

	std::shared_ptr<PhysicsBody> A;
	std::shared_ptr<PhysicsBody> B;

	s2d::NormalVec normal;
	float seperation;
	std::array<s2d::Point, 2> contactPoints;
};

