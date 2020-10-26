#include "include.h"
#include "SFMLHelpers.h"

Vector2f lerp(const Vector2f& a, const Vector2f& b, const float t) {
	return Vector2f(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

float lerp(const float a, const float b, const float t) {
	return a + t * (b - a);
}

//inline ostream& operator<<(ostream& os, const Vector2f& rhs) {
//	os << "sf::Vector2f(" << rhs.x << "," << rhs.y << ")";
//	return os;
//}

//inline ostream& operator<<(ostream& os, const Vector2i& rhs) {
//	os << "sf::Vector2i(" << rhs.x << "," << rhs.y << ")";
//	return os;
//}

//inline ostream& operator<<(ostream& os, const Vector2u& rhs) {
//	os << "sf::Vector2u(" << rhs.x << "," << rhs.y << ")";
//	return os;
//}