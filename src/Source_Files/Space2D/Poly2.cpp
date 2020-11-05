#include "include.h"
#include "Poly2.h"
#include "Point2.h"
#include "Vec2.h"
#include "NormalizedVec2.h"
#include "Dimension2.h"
#include "Rect2.h"

using namespace Space2D;


using Point = Point2;
using Vec = Vec2;
using NormalVec = NormalizedVec2;
using Dimension = Dimension2;
using Rect = Rect2;


Poly2::Poly2() noexcept : points(std::vector<Point>(1, Point())), cent(Point(0, 0)) {}

Poly2::Poly2(const std::vector<Point>& points) noexcept : points(points), cent(calc_centroid()) {

}

Poly2::Poly2(const std::vector<Point>& points0_to_1, const Rectangle& quad_dim) noexcept : points(points0_to_1) {
    auto len = points.size();
    for (size_t i = 0; i < len; i++) {
        auto& p = points.at(i);
        p.x = lerp(quad_dim.min.x, quad_dim.max.x, p.x);
        p.y = lerp(quad_dim.min.y, quad_dim.max.y, p.y);
    }

    cent = calc_centroid();
}

Poly2::Poly2(const Rectangle& quad_dim) noexcept : points({ Point(0,0), Point(1,0), Point(1,1), Point(0,1) }) {
    auto len = points.size();
    for (size_t i = 0; i < len; i++) {
        auto& p = points.at(i);
        p.x = lerp(quad_dim.min.x, quad_dim.max.x, p.x);
        p.y = lerp(quad_dim.min.y, quad_dim.max.y, p.y);
    }
    cent = calc_centroid();
}

const Point& Poly2::operator[] (const size_t i) const {
    return points[i];
}


Point* Poly2::begin() { return &*points.begin(); }
const Point* Poly2::begin() const { return &*points.begin(); }
Point* Poly2::end() { return &*points.end(); }
const Point* Poly2::end() const { return &*points.end(); }

const Point& Poly2::centroid() const {
    return cent;
}

NormalVec Poly2::normal(const unsigned int i) const {
    unsigned int j = i < points.size() - 1 ? i + 1 : 0;
    return Vec((*this)[i], (*this)[j]).unitNormal();
}

bool Poly2::operator==(const Poly2& other) const {
    if (size() != other.size()) return false;
    if (cent != other.cent) return false;
    size_t len = size();
    size_t i = 0;
    bool eq = true;
    while (i < len && eq) {
        eq = eq && points[i] == other[i];
        i++;
    }
    return eq;
}

bool Poly2::operator!= (const Poly2& other) const noexcept {
    return !(operator==(other));
}

Poly2& Poly2::operator-=(const Vec& rhs) noexcept {
    auto len = size();
    for (size_t i = 0; i < len; i++) {
        points[i] -= rhs;
    }

    cent -= rhs;

    return *this;
}

Poly2 Poly2::operator-(const Vec& rhs) const noexcept {
    auto len = size();
    Point newcent = cent - rhs;
    std::vector<Point> newpoints;
    newpoints.reserve(len);
    for (size_t i = 0; i < len; i++) {
        newpoints.push_back(points[i] - rhs);
    }
    return Poly2(newpoints, newcent);
}

Poly2& Poly2::operator-=(const NormalVec& rhs) noexcept {
    auto len = size();
    for (size_t i = 0; i < len; i++) {
        points[i] -= rhs;
    }

    cent -= rhs;

    return *this;
}

Poly2 Poly2::operator-(const NormalVec& rhs) const noexcept {
    auto len = size();
    Point newcent = cent - rhs;
    std::vector<Point> newpoints;
    newpoints.reserve(len);
    for (size_t i = 0; i < len; i++) {
        newpoints.push_back(points[i] - rhs);
    }
    return Poly2(newpoints, newcent);
}

Poly2& Poly2::operator+=(const Vec& rhs) noexcept {
    auto len = size();
    for (size_t i = 0; i < len; i++) {
        points[i] += rhs;
    }

    cent += rhs;

    return *this;
}

Poly2 Poly2::operator+(const Vec& rhs) const noexcept {
    auto len = size();
    Point newcent = cent + rhs;
    std::vector<Point> newpoints;
    newpoints.reserve(len);
    for (size_t i = 0; i < len; i++) {
        newpoints.push_back(points[i] + rhs);
    }
    return Poly2(newpoints, newcent);
}

Poly2& Poly2::operator+=(const NormalVec& rhs) noexcept {
    auto len = size();
    for (size_t i = 0; i < len; i++) {
        points[i] += rhs;
    }

    cent += rhs;

    return *this;
}

Poly2 Poly2::operator+(const NormalVec& rhs) const noexcept {
    auto len = size();
    Point newcent = cent + rhs;
    std::vector<Point> newpoints;
    newpoints.reserve(len);
    for (size_t i = 0; i < len; i++) {
        newpoints.push_back(points[i] + rhs);
    }
    return Poly2(newpoints, newcent);
}

float Poly2::area() const noexcept {
    float a = 0.0;

    auto len = size();
    auto j = len - 1;
    for (auto i = 0; i < len; i++)
    {
        a += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;
    }
    return abs(a / 2.0f);
}

size_t Poly2::size() const noexcept {
    return points.size();
}

Rectangle Poly2::getAABB() const noexcept {
    float minx = points[0].x;
    float miny = points[0].y;
    float maxx = points[0].x;
    float maxy = points[0].y;
    auto len = size();
    for (size_t i = 1; i < size(); i++) {
        minx = min(minx, points[i].x);
        maxx = max(maxx, points[i].x);

        miny = min(miny, points[i].y);
        maxy = max(maxy, points[i].y);
    }
    return Rectangle(Point(minx, miny), Point(maxx, maxy));
}

Point Poly2::calc_centroid() const noexcept {
    Point cent;

    auto len = points.size();
    double signedArea = 0;

    for (size_t i = 0; i < len - 1; i++) {

        double x0 = points[i].x;
        double y0 = points[i].y;
        double x1 = points[i + 1].x;
        double y1 = points[i + 1].y;

        double A = (x0 * y1) - (x1 * y0);
        signedArea += A;

        cent.x += static_cast<float>((x0 + x1) * A);
        cent.y += static_cast<float>((y0 + y1) * A);
    }

    double x0 = points[len - 1].x;
    double y0 = points[len - 1].y;
    double x1 = points[0].x;
    double y1 = points[0].y;

    double A = (x0 * y1) - (x1 * y0);
    signedArea += A;

    cent.x += static_cast<float>((x0 + x1) * A);
    cent.y += static_cast<float>((y0 + y1) * A);

    signedArea *= 0.5;
    cent.x /= static_cast<float>((6 * signedArea));
    cent.y /= static_cast<float>((6 * signedArea));

    return cent;
}

Poly2::Poly2(const std::vector<Point>& points, const Point& centroid) noexcept : points(points), cent(centroid) {}