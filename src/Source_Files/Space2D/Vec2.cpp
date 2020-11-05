#include "include.h"
#include "Vec2.h"
#include "NormalizedVec2.h"
#include "Point2.h"

using namespace Space2D;

using Vec = Vec2;
using NormalVec = NormalizedVec2;
using Point = Point2;

//defaults to (0,0)
Vec2::Vec2()  noexcept : x(0), y(0) {}

Vec2::Vec2(const float& x, const float& y) noexcept : x(x), y(y) {}

//define a vector as the distance from two points in the direction from start to end
Vec2::Vec2(const Point& start, const Point& end) noexcept : x(end.x - start.x), y(end.y - start.y) {}

//construct a vector from a normal vector
Vec2::Vec2(const NormalVec& vec) noexcept : x(vec.x), y(vec.y) {}

const float& Vec2::operator[] (const unsigned int i) const noexcept {
	return i == 0 ? x : y;
}

float& Vec2::operator[] (const unsigned int i) noexcept {
	return i == 0 ? x : y;
}

Vec Vec2::operator-() const noexcept {
	return Vec(-x, -y);
}

bool Vec2::operator==(const Vec& other) const noexcept {
	return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
}

bool Vec2::operator!=(const Vec& other) const noexcept {
	return !(operator==(other));
}

Vec& Vec2::operator-=(const Vec& rhs) noexcept {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec& Vec2::operator-=(const NormalVec& rhs) noexcept {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec Vec2::operator-(const Vec& rhs) const noexcept {
	return Vec(x - rhs.x, y - rhs.y);
}

Vec Vec2::operator-(const NormalVec& rhs) const noexcept {
	return Vec(x - rhs.x, y - rhs.y);
}

Vec& Vec2::operator+=(const Vec& rhs) noexcept {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec& Vec2::operator+=(const NormalVec& rhs) noexcept {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec Vec2::operator+(const Vec& rhs) const noexcept {
	return Vec(x + rhs.x, y + rhs.y);
}

Vec Vec2::operator+(const NormalVec& rhs) const noexcept {
	return Vec(x + rhs.x, y + rhs.y);
}

Vec& Vec2::operator*=(const float& factor) noexcept {
	x *= factor;
	y *= factor;
	return *this;
}

Vec Vec2::operator*(const float& factor) const noexcept {
	return Vec(x * factor, y * factor);
}

float Vec2::Dot(const Vec& other) const noexcept {
	return x * other.x + y * other.y;
}

float Vec2::Dot(const NormalVec& other) const noexcept {
	return x * other.x + y * other.y;
}

NormalVec  Vec2::Normalize() const {
	return NormalVec(x, y);
}

float Vec2::Mag() const noexcept {
	return std::sqrt(x * x + y * y);
}

float Vec2::MagSquared() const noexcept {
	return x * x + y * y;
}

bool Vec2::perp(const Vec& other) const noexcept {
	return std::abs(Dot(other)) < 1e-6;
}

bool Vec2::perp(const NormalVec& other) const noexcept {
	return std::abs(Dot(other)) < 1e-6;
}

//unit normal rule: (x, y) -> (y, -x)
NormalVec Vec2::unitNormal() const noexcept {
	return NormalVec(this->y, -this->x);
}