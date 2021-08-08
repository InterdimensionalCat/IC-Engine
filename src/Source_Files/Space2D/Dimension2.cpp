//#include "include.h"
//#include "Dimension2.h"
//#include "Point2.h"
//#include "Vec2.h"
//#include "NormalizedVec2.h"
//
//
//
//using namespace Space2D;
//
//using Point = Point2;
//using Vec = Vec2;
//using NormalVec = NormalizedVec2;
//using Dimension = Dimension2;
//
//Dimension2::Dimension2()  noexcept : x(0), y(0) {}
//
//Dimension2::Dimension2(const float& x, const float& y) noexcept : x(x), y(y) {}
//
//Dimension2::Dimension2(const Point& min, const Point& max) noexcept : x(max.x - min.x), y(max.y - min.y) {}
//
//Dimension2::Dimension2(const Point& other) noexcept : x(other.x), y(other.y) {}
//
//Dimension2::Dimension2(const Vec& other) noexcept : x(other.x), y(other.y) {}
//
//const float& Dimension2::operator[] (const unsigned int i) const noexcept {
//    return i == 0 ? x : y;
//}
//
//float& Dimension2::operator[] (const unsigned int i) noexcept {
//    return i == 0 ? x : y;
//}
//
//bool Dimension2::operator==(const Dimension& other) const noexcept {
//    return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
//}
//
//bool Dimension2::operator!=(const Dimension& other) const noexcept {
//    return !(operator==(other));
//}
//
//Dimension& Dimension2::operator-=(const Dimension& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Dimension& Dimension2::operator-=(const Vec& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Dimension& Dimension2::operator-=(const NormalVec& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Dimension Dimension2::operator-(const Dimension& rhs) const noexcept {
//    return Dimension(x - rhs.x, y - rhs.y);
//}
//
//Dimension Dimension2::operator-(const Vec& rhs) const noexcept {
//    return Dimension(x - rhs.x, y - rhs.y);
//}
//
//Dimension Dimension2::operator-(const NormalVec& rhs) const noexcept {
//    return Dimension(x - rhs.x, y - rhs.y);
//}
//
//Dimension& Dimension2::operator+=(const Dimension& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Dimension& Dimension2::operator+=(const Vec& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Dimension& Dimension2::operator+=(const NormalVec& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Dimension Dimension2::operator+(const Dimension& rhs) const noexcept {
//    return Dimension(x + rhs.x, y + rhs.y);
//}
//
//Dimension Dimension2::operator+(const Vec& rhs) const noexcept {
//    return Dimension(x + rhs.x, y + rhs.y);
//}
//
//Dimension Dimension2::operator+(const NormalVec& rhs) const noexcept {
//    return Dimension(x + rhs.x, y + rhs.y);
//}
//
//Dimension& Dimension2::operator*=(const float& factor) noexcept {
//    x *= factor;
//    y *= factor;
//    return *this;
//}
//
//Dimension Dimension2::operator*(const float& factor) const noexcept {
//    return Dimension(x * factor, y * factor);
//}
//
//Dimension& Dimension2::operator/=(const float& factor) noexcept {
//    x /= factor;
//    y /= factor;
//    return *this;
//}
//
//Dimension Dimension2::operator/(const float& factor) const noexcept {
//    return Dimension(x / factor, y / factor);
//}