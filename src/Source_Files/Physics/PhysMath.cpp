#include "include.h"
#include "PhysMath.h"
#include"PolygonBody.h"


Projection::Projection(float mi, float ma) : min(mi), max(ma) {}

Projection::Projection() : min(numeric_limits<float>::infinity()), max(-numeric_limits<float>::infinity()) {}


Vector2f projectVec(const Vector2f &projectAxis, const Vector2f &angleAxis) {
	float length = VecDot(projectAxis, angleAxis) /
		(VecSqrLen(angleAxis));
	return angleAxis * length;
}


Projection projectShape(const PolygonBody shape, const Vector2f &angleAxis) {
	//initialize to first possible value
	Projection proj;

	//iterate through the rest of the vertices

	for (const Edge &edge : shape.edges) {
		proj.max = std::max(VecDot(angleAxis, edge.start), proj.max);
		proj.min = std::min(VecDot(angleAxis, edge.start), proj.min);
	}

	//assert(proj.min != numeric_limits<float>::infinity() &&
	//	proj.max != -numeric_limits<float>::infinity());

	if (proj.min == numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(proj.min);
#endif
	}

	if (proj.max == -numeric_limits<float>::infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(proj.max);
#endif
	}

	return proj;
}

float projectOverlap(const Projection &a, const Projection &b) {
	return min(a.max, b.max) - max(a.min, b.min);
}


