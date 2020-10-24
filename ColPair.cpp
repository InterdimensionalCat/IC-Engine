#include "include.h"
#include "ColPair.h"
#include "PhysicsBody.h"
#include "GameTransform.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "collisionEvent.h"
#include "Composite.h"



ColPair::ColPair(PhysicsBody* bodyA, PhysicsBody* bodyB) {

	if (bodyA->getType() > bodyB->getType()) {
		A = bodyA;
		B = bodyB;
	}
	else {
		if (bodyA->getType() < bodyB->getType()) {
			A = bodyB;
			B = bodyA;
		}
		else {
			if (bodyA < bodyB) {
				A = bodyA;
				B = bodyB;
			}
			else {
				A = bodyB;
				B = bodyA;
			}
		}
	}


	friction = sqrt(A->getFriction() * B->getFriction());

	static bool(* const SAT[3][3]) (ColPair &pair) = { 

	{RigidPairSAT, dummySAT, dummySAT},
	{RigidStaticSAT, dummySAT, dummySAT},
	{RigidOneWaySAT ,dummySAT, dummySAT}

	};

	valid = SAT[A->getType()][B->getType()](*this);
	if (valid) {
		A->getParent()->collisionInfo.push_back(CollisionEvent(A, B, -normal, -seperation, contactEdge));
		B->getParent()->collisionInfo.push_back(CollisionEvent(A, B, normal, seperation, contactEdge));
	}
}

void ColPair::preUpdate(float invDT) {
	const float allowedPen = 0.1f;
	const float biasFactor = 0.2f;
	normalMass = A->getInvMass() + B->getInvMass();
	normalMass = 1.0f / normalMass;

	Vector2f tangent = Vector2f(1.0f * normal.y, -1.0f * normal.x);
	tangentMass = normalMass;
	bias = -biasFactor * invDT * min(0.0f, seperation + allowedPen);

	Vector2f initialImp = normal * accImp + accTan * tangent;
	A->getParent()->addVelocity( -(A->getInvMass() * initialImp));
	B->getParent()->addVelocity(B->getInvMass() * initialImp);
}

void ColPair::solveCollision() {

	//calculate reletive velocity
	auto reletiveVelocity = B->getVelocity() - A->getVelocity();

	//calculate the velocity along the normal
	float velAlongNormal = VecDot(reletiveVelocity, normal);
	auto dimp = normalMass * (-velAlongNormal + bias);

	//compute accumulated impulse
	auto oldimp = accImp;
	accImp = std::max(0.0f, oldimp + dimp);
	dimp = accImp - oldimp;

	auto normImp = dimp * normal;

	//reduce the velocity of both so that the velocity along the normal is 0
	A->getParent()->addVelocity( -(normImp * A->getInvMass()));
	B->getParent()->addVelocity(normImp * B->getInvMass());


	reletiveVelocity = B->getVelocity() - A->getVelocity();

	Vector2f tangent = Vector2f(1.0f * normal.y, -1.0f * normal.x);
	float velAlongTan = VecDot(reletiveVelocity, tangent);
	float dtan = tangentMass * (-velAlongTan);

	float maxFric = friction * accImp;

	float oldtan = accTan;
	accTan = max(-maxFric, min(oldtan + dtan, maxFric));
	dtan = accTan - oldtan;

	auto tanImp = dtan * tangent;
	A->getParent()->addVelocity( -(tanImp * A->getInvMass()));
	B->getParent()->addVelocity(tanImp * B->getInvMass());
}

void ColPair::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	ConvexShape shape;
	shape.setPointCount(4);
	shape.setPoint(0, contactEdge.start + contactEdge.normal * 0.01f);
	shape.setPoint(1, contactEdge.start - contactEdge.normal * 0.01f);
	shape.setPoint(2, contactEdge.end - contactEdge.normal * 0.01f);
	shape.setPoint(3, contactEdge.end + contactEdge.normal * 0.01f);

	shape.setOutlineColor(Color::Yellow);
	shape.setFillColor(Color::Yellow);
	shape.setOutlineThickness(1);
	target.draw(shape, states);
}

bool ColPair::operator==(const ColPair &other) {
	bool AEqual = A == other.A || A == other.B;
	bool BEqual = B == other.A || B == other.B;
	return AEqual && BEqual;
}

bool RigidPairSAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isActive() && !B->isActive()) return false;
	if (A->getParent() == B->getParent() && A->getParent() != nullptr) {
		return false;
	}

	float leastPen = numeric_limits<float>::infinity();
	Edge bestEdge;

	//get translated polygons
	auto abody = A->getBody();
	auto bbody = B->getBody();

	//difference in positions between a and b
	Vector2f posDiff = B->getCentroid() - A->getCentroid();


	//iterate through shape A normals
	for (auto &edge : abody.edges) {
		auto norm = edge.normal;

		//project both shapes onto the axis
		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && VecDot(bestEdge.normal, posDiff) < 0)) {

			if (!edge.active) {
				continue;
			}

			bestEdge = edge;
			leastPen = projOverlap;
		}
	}

	//iterate through shape B normals
	for (auto &edge : bbody.edges) {
		auto norm = edge.normal;

		//project both shapes onto the axis
		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && VecDot(bestEdge.normal, posDiff) < 0) && edge.active) {


			if (!edge.active) {
				continue;
			}


			bestEdge = edge;
			leastPen = projOverlap;
		}
	}

	//assert(leastPen != numeric_limits<float>::infinity());
	if (leastPen == numeric_limits<float>::infinity()) {
		throw BadInfinityException<float>(leastPen);
	}

	pair.normal = bestEdge.normal;


	auto D1 = B->getCentroid() - A->getCentroid();
	auto D2 = pair.normal;

	if (VecDot(D1, D2) < 0) {
		pair.normal = -pair.normal;
	}

	assert(pair.contactEdge.active);

	pair.contactEdge = bestEdge;
	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->getParent()->setActive(true);
	for (auto &b : A->neighbors) {
		b->getParent()->setActive(true);
	}
	A->neighbors.clear();
	B->getParent()->setActive(true);
	for (auto &b : B->neighbors) {
		b->getParent()->setActive(true);
	}
	B->neighbors.clear();
	return true;
}

bool RigidStaticSAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isActive() && !B->isActive()) return false;

	float leastPen = numeric_limits<float>::infinity();
	Edge bestEdge;

	//get translated polygons

	auto abody = A->getBody();
	auto bbody = B->getBody();

	//difference in positions between a and b
	Vector2f posDiff = B->getCentroid() - A->getCentroid();


	//iterate through shape A normals
	for (auto &edge : abody.edges) {
		auto norm = edge.normal;

		//project both shapes onto the axis
		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && VecDot(bestEdge.normal, posDiff) < 0)) {

			if (!edge.active) {
				continue;
			}

			bestEdge = edge;
			leastPen = projOverlap;
		}
	}

	//only check polygon B normals, do not update for leastpen
	for (auto &edge : bbody.edges) {
		auto norm = edge.normal;

		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		float projOverlap = projectOverlap(projA, projB);

		if (projOverlap < 0)
			return false;
	}

	if (leastPen == numeric_limits<float>::infinity()) {
		throw BadInfinityException<float>(leastPen);
	}

	pair.normal = bestEdge.normal;


	auto D1 = B->getCentroid() - A->getCentroid();
	auto D2 = pair.normal;

	if (VecDot(D1, D2) < 0) {
		pair.normal = -pair.normal;
	}

	assert(pair.contactEdge.active);

	pair.contactEdge = bestEdge;
	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->getParent()->setActive(true);
	for (auto &b : A->neighbors) {
		b->getParent()->setActive(true);
	}
	A->neighbors.clear();

	return true;
}

bool RigidOneWaySAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isActive() && !B->isActive()) return false;

	float leastPen = numeric_limits<float>::infinity();
	Edge bestEdge;

	//get translated polygons

	auto abody = A->getBody();
	auto bbody = B->getBody();

	//difference in positions between a and b
	Vector2f posDiff = B->getCentroid() - A->getCentroid();


	//iterate through shape A normals
	for (auto &edge : abody.edges) {
		auto norm = edge.normal;

		//project both shapes onto the axis
		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && VecDot(bestEdge.normal, posDiff) < 0)) {

			if (!edge.active) {
				continue;
			}

			bestEdge = edge;
			leastPen = projOverlap;
		}
	}

	//only check polygon B normals, do not update for leastpen
	for (auto &edge : bbody.edges) {
		auto norm = edge.normal;

		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		float projOverlap = projectOverlap(projA, projB);

		if (projOverlap < 0)
			return false;
	}

	if (leastPen == numeric_limits<float>::infinity()) {
		throw BadInfinityException<float>(leastPen);
	}

	//check that player is moving opposite the normal

	float dir = VecDot(bestEdge.normal, VecNormalize(B->getVelocity()));

	

	if (dir > 0 && leastPen < abs(VecDot(B->getVelocity(), bestEdge.normal))) {
		return false;
	}

	pair.normal = bestEdge.normal;


	auto D1 = B->getCentroid() - A->getCentroid();
	auto D2 = pair.normal;

	if (VecDot(D1, D2) < 0) {
		pair.normal = -pair.normal;
	}

	assert(pair.contactEdge.active);


	pair.contactEdge = bestEdge;

	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->getParent()->setActive(true);
	for (auto &b : A->neighbors) {
		b->getParent()->setActive(true);
	}
	A->neighbors.clear();

	return true;
}

bool dummySAT(ColPair &pair) {
	return false;
}

void ColPair::update(const ColPair& other) {
	normal = other.normal;
	contactEdge = other.contactEdge;
	seperation = other.seperation;

	//removing these lines causes warmstarting
	//warmstarting no longer possible with this function depriciated
	accImp = 0.0f;
	accPos = 0.0f;
	accTan = 0.0f;
}