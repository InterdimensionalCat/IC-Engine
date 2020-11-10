#include "include.h"
#include "CollisionEvent.h"
#include "PhysicsEngine.h"
#include "PhysicsBody.h"

using namespace s2d;

CollisionEvent::CollisionEvent(PhysicsBody* A, const size_t ABodyNum,
	PhysicsBody* B, const size_t BBodyNum, const NormalVec& normal,
	const float seperation, 
	const std::array<Point, 2>& contactPoints)
: A(A), B(B), normal(normal), seperation(seperation), contactPoints(contactPoints) {}