#include "include.h"
#include "ColPair.h"
#include "PhysicsBody.h"
#include "GameTransform.h"
#include "CollisionEvent.h"
#include "PhysMath.h"
#include "PhysEventHandler.h"

using Point = s2d::GameUnits::Point;
using Vec = s2d::GameUnits::Vec;
using Poly = s2d::GameUnits::Poly;
using Normal_Vec = s2d::GameUnits::Normal_Vec;

ColPair::ColPair(PhysicsBody* bodyA, const size_t& ANum, PhysicsBody* bodyB, const size_t& BNum) {

	if (bodyA->getType() > bodyB->getType()) {
		A = bodyA;
		B = bodyB;
		ABodyNum = ANum;
		BBodyNum = BNum;
	}
	else {
		if (bodyA->getType() < bodyB->getType()) {
			A = bodyB;
			B = bodyA;
			ABodyNum = BNum;
			BBodyNum = ANum;
		}
		else {
			if (bodyA < bodyB) {
				A = bodyA;
				B = bodyB;
				ABodyNum = ANum;
				BBodyNum = BNum;
			}
			else {
				A = bodyB;
				B = bodyA;
				ABodyNum = BNum;
				BBodyNum = ANum;
			}
		}
	}


	friction = sqrt(A->getFriction() * B->getFriction());

	static bool(* const SAT[3][3]) (ColPair &pair) = { 

	{RigidPairSAT, dummySAT, dummySAT},
	{RigidStaticSAT, dummySAT, dummySAT},
	{RigidOneWaySAT ,dummySAT, dummySAT}

	};

	valid = SAT[(int)A->getType()][(int)B->getType()](*this);
	if (valid) {
		if (A->getInfo()) {
			A->getInfo()->events.push_back(CollisionEvent(A, ABodyNum, B, BBodyNum, normal, -seperation, contactPoints));
		}
		if (B->getInfo()) {
			B->getInfo()->events.push_back(CollisionEvent(A, ABodyNum, B, BBodyNum, normal, seperation, contactPoints));
		}

		//A->getParent()->collisionInfo.push_back(CollisionEvent(A, B, -normal, -seperation, contactEdge));
		//B->getParent()->collisionInfo.push_back(CollisionEvent(A, B, normal, seperation, contactEdge));
	}
}

void ColPair::preUpdate(float invDT) {
	const float allowedPen = 0.1f;
	const float biasFactor = 0.2f;
	normalMass = A->getInvMass() + B->getInvMass();
	normalMass = 1.0f / normalMass;

	Vec tangent = Vec(1.0f * normal.y, -1.0f * normal.x);
	tangentMass = normalMass;
	bias = -biasFactor * invDT * min(0.0f, seperation + allowedPen);

	Vec initialImp = normal * accImp +  tangent * accTan;
	A->addVelocity( -(initialImp * A->getInvMass()));
	B->addVelocity(initialImp * B->getInvMass());
}

void ColPair::solveCollision() {

	//calculate reletive velocity
	auto reletiveVelocity = B->getVelocity() - A->getVelocity();

	//calculate the velocity along the normal
	float velAlongNormal = reletiveVelocity.Dot(normal);
	auto dimp = normalMass * (-velAlongNormal + bias);

	//compute accumulated impulse
	auto oldimp = accImp;
	accImp = std::max(0.0f, oldimp + dimp);
	dimp = accImp - oldimp;

	auto normImp = normal * dimp;

	//reduce the velocity of both so that the velocity along the normal is 0

	A->addVelocity( -(normImp * A->getInvMass()));
	B->addVelocity(normImp * B->getInvMass());


	reletiveVelocity = B->getVelocity() - A->getVelocity();

	Vec tangent = Vec(1.0f * normal.y, -1.0f * normal.x);
	float velAlongTan = reletiveVelocity.Dot(tangent);
	float dtan = tangentMass * (-velAlongTan);

	float maxFric = friction * accImp;

	float oldtan = accTan;
	accTan = max(-maxFric, min(oldtan + dtan, maxFric));
	dtan = accTan - oldtan;

	auto tanImp = tangent * dtan;
	A->addVelocity( -(tanImp * A->getInvMass()));
	B->addVelocity(tanImp * B->getInvMass());
}

bool ColPair::operator==(const ColPair &other) {
	bool AEqual = A == other.A || A == other.B;
	bool BEqual = B == other.A || B == other.B;
	bool AindEqual = ABodyNum == other.ABodyNum || ABodyNum == other.BBodyNum;
	bool BindEqual = BBodyNum == other.BBodyNum || BBodyNum == other.ABodyNum;
	return AEqual && BEqual && AindEqual && BindEqual;
}

bool RigidPairSAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isAwake() && !B->isAwake()) return false;

	float leastPen = numeric_limits<float>::infinity();
	Vec bestAxis;
	Point bestpoints[2];

	//get translated polygons
	Poly abody = pair.A->getBodies()[pair.ABodyNum];
	Poly bbody = pair.B->getBodies()[pair.BBodyNum];

	//difference in positions between a and b
	Point posDiff = bbody.centroid() - abody.centroid();
	auto posDiffVec = Vec(posDiff.x, posDiff.y);


	//iterate through shape A normals
	for (size_t i = 0; i < abody.size(); i++) {
		Vec edgeVec;
		Point edgepoints[2];
		if (i >= abody.size() - 1) {
			edgeVec = Vec(abody[i], abody[0]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[0];
		}
		else {
			edgeVec = Vec(abody[i], abody[i + 1]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[i + 1];
		}
		auto norm = edgeVec.unitNormal();

		//project both shapes onto the axis
		Projection projA = projectShape(abody, norm);
		Projection projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && norm.Dot(posDiffVec) < 0)) {

			if (!A->isEdgeActive(pair.ABodyNum, i)) {
				continue;
			}

			bestAxis = edgeVec;
			bestpoints[0] = edgepoints[0];
			bestpoints[1] = edgepoints[1];
			leastPen = projOverlap;
		}
	}

	//iterate through shape B normals
	for (size_t i = 0; i < bbody.size(); i++) {
		Vec edgeVec;
		Point edgepoints[2];
		if (i >= abody.size() - 1) {
			edgeVec = Vec(bbody[i], bbody[0]);
			edgepoints[0] = bbody[i];
			edgepoints[1] = bbody[0];
		}
		else {
			edgeVec = Vec(bbody[i], bbody[i + 1]);
			edgepoints[0] = bbody[i];
			edgepoints[1] = bbody[i + 1];
		}
		auto norm = edgeVec.unitNormal();

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
			|| (projOverlap == leastPen && norm.Dot(posDiffVec) < 0)) {

			if (!B->isEdgeActive(pair.BBodyNum, i)) {
				continue;
			}

			bestAxis = edgeVec;
			bestpoints[0] = edgepoints[0];
			bestpoints[1] = edgepoints[1];
			leastPen = projOverlap;
		}
	}

#ifdef _DEBUG
	if (leastPen == numeric_limits<float>::infinity()) {
		throw BadInfinityException<float>(leastPen);
	}
#endif
	pair.normal = bestAxis.unitNormal();


	auto D1 = bbody.centroid() - abody.centroid();
	auto D1Vec = Vec(D1.x, D1.y);
	auto D2 = pair.normal;

	if (D2.Dot(D1Vec) < 0) {
		pair.normal = -pair.normal;
	}

	//pair.contactPlane = bestAxis;
	pair.contactPoints = { bestpoints[0], bestpoints[1] };
	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->setAwake(true);
	for (auto &b : A->getNeighbors()) {
		b->setAwake(true);
	}
	A->getNeighbors().clear();

	B->setAwake(true);
	for (auto& b : B->getNeighbors()) {
		b->setAwake(true);
	}
	B->getNeighbors().clear();
	return true;
}

bool RigidStaticSAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isAwake() && !B->isAwake()) return false;

	float leastPen = numeric_limits<float>::infinity();
	Vec bestAxis;
	Point bestpoints[2];

	//get translated polygons
	Poly abody = pair.A->getBodies()[pair.ABodyNum];
	Poly bbody = pair.B->getBodies()[pair.BBodyNum];

	//difference in positions between a and b
	Point posDiff = bbody.centroid() - abody.centroid();
	auto posDiffVec = Vec(posDiff.x, posDiff.y);


	//iterate through shape A normals
	for (size_t i = 0; i < abody.size(); i++) {
		Vec edgeVec;
		Point edgepoints[2];
		if (i >= abody.size() - 1) {
			edgeVec = Vec(abody[i], abody[0]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[0];
		}
		else {
			edgeVec = Vec(abody[i], abody[i + 1]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[i + 1];
		}
		auto norm = edgeVec.unitNormal();

		//project both shapes onto the axis
		Projection projA = projectShape(abody, norm);
		Projection projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && norm.Dot(posDiffVec) < 0)) {

			if (!A->isEdgeActive(pair.ABodyNum, i)) {
				continue;
			}

			bestAxis = edgeVec;
			bestpoints[0] = edgepoints[0];
			bestpoints[1] = edgepoints[1];
			leastPen = projOverlap;
		}
	}

	//only check polygon B normals, do not update for leastpen
	for (size_t i = 0; i < bbody.size(); i++) {
		Vec edgeVec;
		if (i >= abody.size() - 1) {
			edgeVec = Vec(bbody[i], bbody[0]);
		}
		else {
			edgeVec = Vec(bbody[i], bbody[i + 1]);
		}
		auto norm = edgeVec.unitNormal();

		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		float projOverlap = projectOverlap(projA, projB);

		if (projOverlap < 0)
			return false;
	}

	if (leastPen == numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(leastPen);
#endif
	}
	pair.normal = bestAxis.unitNormal();


	auto D1 = bbody.centroid() - abody.centroid();
	auto D1Vec = Vec(D1.x, D1.y);
	auto D2 = pair.normal;

	if (D2.Dot(D1Vec) < 0) {
		pair.normal = -pair.normal;
	}

	pair.contactPoints = { bestpoints[0], bestpoints[1] };
	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->setAwake(true);
	for (auto& b : A->getNeighbors()) {
		b->setAwake(true);
	}
	A->getNeighbors().clear();

	return true;
}

bool RigidOneWaySAT(ColPair &pair) {

	PhysicsBody* A = pair.A;
	PhysicsBody* B = pair.B;

	if (!A->isAwake() && !B->isAwake()) return false;

	float leastPen = numeric_limits<float>::infinity();
	Vec bestAxis;
	Point bestpoints[2];

	//get translated polygons
	Poly abody = pair.A->getBodies()[pair.ABodyNum];
	Poly bbody = pair.B->getBodies()[pair.BBodyNum];

	//difference in positions between a and b
	Point posDiff = bbody.centroid() - abody.centroid();
	auto posDiffVec = Vec(posDiff.x, posDiff.y);


	//iterate through shape A normals
	for (size_t i = 0; i < abody.size(); i++) {
		Vec edgeVec;
		Point edgepoints[2];
		if (i >= abody.size() - 1) {
			edgeVec = Vec(abody[i], abody[0]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[0];
		}
		else {
			edgeVec = Vec(abody[i], abody[i + 1]);
			edgepoints[0] = abody[i];
			edgepoints[1] = abody[i + 1];
		}
		auto norm = edgeVec.unitNormal();

		//project both shapes onto the axis
		Projection projA = projectShape(abody, norm);
		Projection projB = projectShape(bbody, norm);

		//calculate the penetration distance on this axis
		float projOverlap = projectOverlap(projA, projB);

		//if there is a negative overlap the SAT fail,
		//indicating no collision
		if (projOverlap < 0)
			return false;
		if (projOverlap < leastPen
			|| (projOverlap == leastPen && norm.Dot(posDiffVec) < 0)) {

			if (!A->isEdgeActive(pair.ABodyNum, i)) {
				continue;
			}

			bestAxis = edgeVec;
			leastPen = projOverlap;
		}
	}

	//only check polygon B normals, do not update for leastpen
	for (size_t i = 0; i < bbody.size(); i++) {
		Vec edgeVec;
		if (i >= abody.size() - 1) {
			edgeVec = Vec(bbody[i], bbody[0]);
		}
		else {
			edgeVec = Vec(bbody[i], bbody[i + 1]);
		}
		auto norm = edgeVec.unitNormal();

		auto projA = projectShape(abody, norm);
		auto projB = projectShape(bbody, norm);

		float projOverlap = projectOverlap(projA, projB);

		if (projOverlap < 0)
			return false;
	}

	if (leastPen == numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(leastPen);
#endif
	}

	//check that player is moving opposite the normal

	float dir = bestAxis.unitNormal().Dot(B->getVelocity().Normalize());

	

	if (dir > 0 && leastPen < abs(bestAxis.unitNormal().Dot(B->getVelocity()))) {
		return false;
	}

	pair.normal = bestAxis.unitNormal();


	auto D1 = bbody.centroid() - abody.centroid();
	auto D1Vec = Vec(D1.x, D1.y);
	auto D2 = pair.normal;

	if (D2.Dot(D1Vec) < 0) {
		pair.normal = -pair.normal;
	}

	pair.contactPoints = { bestpoints[0], bestpoints[1] };
	pair.seperation = -leastPen;
	//all axis tested, collision occured
	A->setAwake(true);
	for (auto& b : A->getNeighbors()) {
		b->setAwake(true);
	}
	A->getNeighbors().clear();

	return true;
}

bool dummySAT(ColPair &pair) {
#ifdef _DEBUG
	cerr << "invalid collision pair!\n";
	throw exception();
#endif
	return false;
}

void ColPair::update(const ColPair& other) {
	normal = other.normal;
	contactPoints = other.contactPoints;
	seperation = other.seperation;

	//removing these lines causes warmstarting
	//warmstarting no longer possible with this function depriciated
	accImp = 0.0f;
	accPos = 0.0f;
	accTan = 0.0f;
}