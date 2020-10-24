#pragma once
#include "include.h"

Vector2f lerp(const Vector2f &a, const Vector2f &b, const float t) {
	return Vector2f(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

float lerp(const float a, const float b, const float t) {
	return a + t * (b - a);
}

inline ostream & operator<<(ostream &os, const Vector2f &rhs) {
	os << "X: " << rhs.x << " Y: " << rhs.y;
	return os;
}

inline ostream & operator<<(ostream &os, const Vector2D &rhs) {
	os << "X: " << rhs.x << " Y: " << rhs.y;
	return os;
}