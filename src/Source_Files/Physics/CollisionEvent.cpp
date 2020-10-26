#include "include.h"
#include "CollisionEvent.h"
#include "PhysicsEngine.h"
#include "PhysicsBody.h"
#include "PolygonBody.h"

CollisionEvent::CollisionEvent(PhysicsBody* A, PhysicsBody* B, const Vector2f normal, const float seperation, const Edge contactEdge) : A(A), B(B), normal(Vector2f(normal.x, normal.y)), seperation(seperation), contactEdge(contactEdge) {}