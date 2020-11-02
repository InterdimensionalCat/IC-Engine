#include "include.h"
#include "PhysMath.h"


using Poly = s2d::GameUnits::Poly;
using Vec = s2d::GameUnits::Vec;

using Normal_vec = s2d::GameUnits::Normal_Vec;

Projection::Projection(float mi, float ma) : min(mi), max(ma) {}

Projection::Projection() : min(numeric_limits<float>::infinity()), max(-numeric_limits<float>::infinity()) {}


Vec projectVec(const Vec &projectAxis, const Vec &angleAxis) {
	float length = projectAxis.Dot(angleAxis) /
		(angleAxis.MagSquared());
	return angleAxis * length;
}


Projection projectShape(const Poly shape, const s2d::GameUnits::Normal_Vec& angleAxis) {
	//initialize to first possible value
	Projection proj;

	//iterate through the rest of the vertices
	for (size_t i = 0; i < shape.size(); i++) {
		proj.max = std::max(angleAxis.Dot(Vec(shape[i].x, shape[i].y)), proj.max);
		proj.min = std::min(angleAxis.Dot(Vec(shape[i].x, shape[i].y)), proj.min);
	}

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


