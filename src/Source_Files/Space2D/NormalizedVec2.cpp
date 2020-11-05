#include "include.h"
#include "NormalizedVec2.h"
#include "Vec2.h"

using namespace Space2D;

using Vec = Vec2;

NormalizedVec2::NormalizedVec2(const float& x, const float& y) : x(x / std::sqrt(x * x + y * y)), y(y / std::sqrt(x * x + y * y)) {}

//constructor from radian angle value
NormalizedVec2::NormalizedVec2(const Radians radians) noexcept : x(static_cast<float>(std::cos(radians.get()))), y(static_cast<float>(std::sin(radians.get()))) {}


const float& NormalizedVec2::operator[] (const unsigned int i) const {
    return i == 0 ? x : y;
}

NormalizedVec2 NormalizedVec2::operator- () const noexcept {
    return NormalizedVec2(-x, -y);
}

bool NormalizedVec2::operator==(const NormalizedVec2& other) const noexcept {
    return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
}

bool NormalizedVec2::operator!= (const NormalizedVec2& other) const noexcept {
    return !(operator==(other));
}

Vec NormalizedVec2::operator-(const NormalizedVec2& rhs) const noexcept {
    return Vec(x - rhs.x, y - rhs.y);
}

Vec NormalizedVec2::operator-(const Vec& rhs) const noexcept {
    return Vec(x - rhs.x, y - rhs.y);
}

Vec NormalizedVec2::operator+(const Vec& rhs) const noexcept {
    return Vec(x + rhs.x, y + rhs.y);
}

Vec NormalizedVec2::operator+(const NormalizedVec2& rhs) const noexcept {
    return Vec(x + rhs.x, y + rhs.y);
}

Vec NormalizedVec2::operator*(const float& factor) const noexcept {
    return Vec(x * factor, y * factor);
}

float NormalizedVec2::Dot(const Vec& other) const noexcept {
    return x * other.x + y * other.y;
}

float NormalizedVec2::Dot(const NormalizedVec2& other) const noexcept {
    return x * other.x + y * other.y;
}

Radians NormalizedVec2::angleOf() const noexcept {
    return Radians(acos(static_cast<float>(x)));
}

bool NormalizedVec2::perp(const Vec& other) const noexcept {
    return std::abs(Dot(other)) < 1e-6;
}

bool NormalizedVec2::perp(const NormalizedVec2& other) const noexcept {
    return std::abs(Dot(other)) < 1e-6;
}