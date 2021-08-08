//#include "include.h"
//#include "Point2.h"
//#include "Vec2.h"
//#include "NormalizedVec2.h"
//#include "Dimension2.h"
//#include <cmath>
//
//using namespace Space2D;
//
//using Point = Point2;
//using Vec = Vec2;
//using NormalVec = NormalizedVec2;
//using Dimension = Dimension2;
//
//
//Point2::Point2()  noexcept : x(0), y(0) {}
//
//Point2::Point2(const float& x, const float& y) noexcept : x(x), y(y) {}
//
//Point2::Point2(const Vec& other) noexcept : x(other.x), y(other.y) {}
//
//Point2::Point2(const Point& base, const Vec& offset) noexcept : x(base.x + offset.x), y(base.y + offset.y) {}
//
//Point2::Point2(const Point& base, const NormalVec& offset) noexcept : x(base.x + offset.x), y(base.y + offset.y) {}
//
//const float& Point2::operator[] (const unsigned int i) const noexcept {
//    return i == 0 ? x : y;
//}
//
//float& Point2::operator[] (const unsigned int i) noexcept {
//    return i == 0 ? x : y;
//}
//
//bool Point2::operator==(const Point& other) const noexcept {
//    return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
//}
//
//bool Point2::operator!= (const Point& other) const noexcept {
//    return !(operator==(other));
//}
//
//Point& Point2::operator-=(const Point& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Point& Point2::operator-=(const Vec& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Point& Point2::operator-=(const NormalVec& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Point& Point2::operator-=(const Dimension& rhs) noexcept {
//    x -= rhs.x;
//    y -= rhs.y;
//    return *this;
//}
//
//Point Point2::operator-(const Point& rhs) const noexcept {
//    return Point(x - rhs.x, y - rhs.y);
//}
//
//Point Point2::operator-(const Vec& rhs) const noexcept {
//    return Point(x - rhs.x, y - rhs.y);
//}
//
//Point Point2::operator-(const NormalVec& rhs) const noexcept {
//    return Point(x - rhs.x, y - rhs.y);
//}
//
//Point Point2::operator-(const Dimension& rhs) const noexcept {
//    return Point(x - rhs.x, y - rhs.y);
//}
//
//Point& Point2::operator+=(const Point& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Point& Point2::operator+=(const Vec& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Point& Point2::operator+=(const NormalVec& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Point& Point2::operator+=(const Dimension& rhs) noexcept {
//    x += rhs.x;
//    y += rhs.y;
//    return *this;
//}
//
//Point Point2::operator+(const Point& rhs) const noexcept {
//    return Point(x + rhs.x, y + rhs.y);
//}
//
//Point Point2::operator+(const Vec& rhs) const noexcept {
//    return Point(x + rhs.x, y + rhs.y);
//}
//
//Point Point2::operator+(const NormalVec& rhs) const noexcept {
//    return Point(x + rhs.x, y + rhs.y);
//}
//
//Point Point2::operator+(const Dimension& rhs) const noexcept {
//    return Point(x + rhs.x, y + rhs.y);
//}
//
//Point& Point2::operator*=(const float& factor) noexcept {
//    x *= factor;
//    y *= factor;
//    return *this;
//}
//
//Point Point2::operator*(const float& factor) const noexcept {
//    return Point(x * factor, y * factor);
//}
//
//Point& Point2::operator/=(const float& factor) noexcept {
//    x /= factor;
//    y /= factor;
//    return *this;
//}