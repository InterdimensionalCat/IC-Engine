#include "include.h"
#include "Rect2.h"
#include "Point2.h"
#include "Vec2.h"
#include "NormalizedVec2.h"
#include "Dimension2.h"

using namespace Space2D;

using Point = Point2;
using Vec = Vec2;
using NormalVec = NormalizedVec2;
using Dimension = Dimension2;

Rect2::Rect2() noexcept {}

Rect2::Rect2(const float& x0, const float& y0, const float& x1, const float& y1) noexcept : min(Point(x0, y0)), max(Point(x1, y1)) {}

Rect2::Rect2(const Point& min, const Point& max) noexcept : min(min), max(max) {}

Rect2::Rect2(const Point& min, const Dimension dim) noexcept : min(min), max(Point(min.x + dim.x, min.y + dim.y)) {}

Rect2::Rect2(const Rect2& base_rect, const Vec& min_offset, const Vec& max_offset) : min(base_rect.min + min_offset), max(base_rect.max - max_offset) {

}

Rect2::Rect2(const Rect2& base_rect, const Percent& min_offset_X, const Percent& min_offset_Y, const Percent& max_offset_X, const Percent& max_offset_Y) {


    min = base_rect.min + Point(base_rect.getWidth() * static_cast<float>(min_offset_X.get() / 100), base_rect.getHeight() * static_cast<float>(min_offset_Y.get() / 100));
    max = base_rect.max - Point(base_rect.getWidth() * static_cast<float>(max_offset_X.get() / 100), base_rect.getHeight() * static_cast<float>(max_offset_Y.get() / 100));
}

bool Rect2::operator==(const Rect2& other) const noexcept {
    return min == other.min && max == other.max;
}

bool Rect2::operator!=(const Rect2& other) const noexcept {
    return !(operator==(other));
}

Rect2& Rect2::operator-=(const Vec& rhs) noexcept {
    min -= rhs;
    max -= rhs;
    return *this;
}

Rect2& Rect2::operator-=(const NormalVec& rhs) noexcept {
    min -= rhs;
    max -= rhs;
    return *this;
}

Rect2 Rect2::operator-(const Vec& rhs) const noexcept {
    return Rect2(min - rhs, max - rhs);
}

Rect2 Rect2::operator-(const NormalVec& rhs) const noexcept {
    return Rect2(min - rhs, max - rhs);
}

Rect2& Rect2::operator+=(const Vec& rhs) noexcept {
    min += rhs;
    max += rhs;
    return *this;
}

Rect2& Rect2::operator+=(const NormalVec& rhs) noexcept {
    min += rhs;
    max += rhs;
    return *this;
}

Rect2 Rect2::operator+(const Vec& rhs) const noexcept {
    return Rect2(min + rhs, max + rhs);
}

Rect2 Rect2::operator+(const NormalVec& rhs) const noexcept {
    return Rect2(min + rhs, max + rhs);
}

float Rect2::area() const noexcept {
    return (getWidth() * getHeight());
}

Point Rect2::center() const noexcept {
    return Point((max.x + min.x) / 2.0f, (max.y + min.y) / 2.0f);
}

bool Rect2::contains(const Point& query) const noexcept {
    return (query.x > min.x) &&
        (query.x < max.x) &&
        (query.y > min.y) &&
        (query.y < max.y);

}

Dimension Rect2::getSize() const noexcept {
    return Dimension(min, max);
}

float Rect2::getWidth() const noexcept {
    return max.x - min.x;
}

float Rect2::getHeight() const noexcept {
    return max.y - min.y;
}

void Rect2::moveMinTo(const Point& new_min) noexcept {
    auto size = getSize();
    min = new_min;
    max = new_min + Vec(size.x, size.y);
}

void Rect2::moveCenterTo(const Point& new_center) noexcept {
    auto size = getSize();
    min = new_center - (size / 2.0f);
    max = new_center + (size / 2.0f);
}

NormalVec Rect2::getNormal_1_0() {
    return NormalVec(static_cast<float>(1), static_cast<float>(0));
}

NormalVec Rect2::getNormal_neg1_0() {
    return NormalVec(static_cast<float>(-1), static_cast<float>(0));
}

NormalVec Rect2::getNormal_0_1() {
    return NormalVec(static_cast<float>(0), static_cast<float>(1));
}

NormalVec Rect2::getNormal_0_neg1() {
    return NormalVec(static_cast<float>(0), static_cast<float>(-1));
}