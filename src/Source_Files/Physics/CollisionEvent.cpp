#include "include.h"
#include "CollisionEvent.h"
#include "PhysicsEngine.h"
#include "PhysicsBody.h"

CollisionEvent::CollisionEvent(PhysicsBody* A, const size_t ABodyNum, 
	PhysicsBody* B, const size_t BBodyNum, const s2d::GameUnits::Normal_Vec& normal, 
	const float seperation, 
	const std::array<s2d::GameUnits::Point, 2>& contactPoints)
: A(A), B(B), normal(normal), seperation(seperation), contactPoints(contactPoints) {}