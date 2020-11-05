#pragma once
#include <numeric>
#include <cmath>
#include "Space2D.h"

class PolygonBody;

//Returns the length of a vector
inline float VecLen(const Vector2f &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

//Returns the square length of a vector
inline float VecSqrLen(const Vector2f &a) {
	return a.x * a.x + a.y * a.y;
}

//Returns the dot product of 2 vectors
//dot product == scalar projection
inline float VecDot(const Vector2f &a, const Vector2f &b) {
	return a.x * b.x + a.y * b.y;
}

//Normalizes a vector (converts it to an angle vector)
inline Vector2f VecNormalize(const Vector2f &a) {
	return a / VecLen(a);
}

//returns true if two vectors are perpindicular
inline bool VecIsPerp(const Vector2f &a, const Vector2f &b) {
	return VecDot(a, b) == 0.0f;
}

//returns the unit normal left hand vector
//normalization rule: (x, y) -> (y, -x)
inline Vector2f UnitNormal(const Vector2f &a) {
	return VecNormalize(Vector2f(a.y, -a.x));
}


//data structure containing scalar projection information
//contains a min and a max
struct Projection {
	Projection(float mi, float ma);
	Projection();
	float min;
	float max;

	//returns true of the interval is well formed
	//(min <= max)
	bool wellFormed() {
		return min <= max;
	}
};

//project one axis onto another
//projection:
//     (A)
//   /
//  /
// ---|--- (B)
//   (A')
// this is projection projectAxis ONTO angleAxis
s2d::Vec projectVec(const s2d::Vec& projectAxis, const s2d::Vec& angleAxis);

//scalar projection of an entire shape onto an axis
//returns a projection in the form (min, max)
//projection:
//      _
//     / /
//    / /
//   /_/
// --x---y---
Projection projectShape(const s2d::Poly shape, const s2d::NormalVec &angleAxis);

//check if two projection vectors overlap
//and return the size of the overlap
//a negative overlap means the objects are not overlapping
//only works if the projections are well formed
float projectOverlap(const Projection &a, const Projection &b);

