#pragma once
#include "Space2D.h"
#include <vector>
#include <algorithm>

namespace Space2D {
    template <typename T, typename SpaceType>
    class Poly2 final
    {

    public:

        using Point = Point2<T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;
        using Normal_Vec = NormalizedVec2<T, SpaceType>;
        using Dimension = Dimension2<T, SpaceType>;
        using Rect = Rect2<T, SpaceType>;
        using Matrix = AffineMatrix<T, SpaceType>;

        //defaults to a single-point polygon with centroid (0,0)
        Poly2() noexcept : points(std::vector<Point>(1, Point())), cent(Point(0,0)) {}

        //construct a polygon directly from a set of points
        explicit Poly2(const std::vector<Point> &points) noexcept : points(points), cent(calc_centroid()) {

            //auto a = signed_doubled_area();

            ////ensure points are in a counter-clockwise fasion
            //if (signed_doubled_area() < 0) {
            //    auto len = points.size();
            //    std::reverse(Poly2::points.begin(), Poly2::points.end());
            //    //vector<Point> rev_points;
            //    //rev_points.reserve(len);
            //    //for (size_t i = 0; i < len; i++) {
            //    //    rev_points.push_back(points[len - i - 1]);
            //    //}
            //    //Poly2::points = rev_points;
            //}

        }

        //construct a polygon from a set of points ranging from zero to one
        //and define their scaled AABB dimensions
        explicit Poly2(const std::vector<Point> &points0_to_1, const Rect &quad_dim) noexcept : points(points0_to_1) {
            auto len = points.size();
            for (size_t i = 0; i < len; i++) {
                auto& p = points[i];
                p.x = SpaceType::lerp(quad_dim.min.x, quad_dim.max.x, p.x);
                p.y = SpaceType::lerp(quad_dim.min.y, quad_dim.max.y, p.y);
            }

            //auto a = signed_doubled_area();

            ////ensure points are in a counter-clockwise fasion
            //if (signed_doubled_area() < 0) {
            //    std::reverse(points.begin(), points.end());
            //    //vector<Point> rev_points;
            //    //rev_points.reserve(len);
            //    //for (size_t i = 0; i < len; i++) {
            //    //    rev_points.push_back(points[len - i - 1]);
            //    //}
            //    //points = rev_points;
            //}

            cent = calc_centroid();
        }

        const Point& operator[] (const size_t i) const {
            return points[i];
        }

        const Point& centroid() const {
            return cent;
        }

        Normal_Vec normal(const unsigned int i) const {
            unsigned int j = i < points.size() - 1 ? i + 1 : 0;
            return Vec((*this)[i], (*this)[j]).unitNormal();
        }


        bool operator==(const Poly2& other) const {
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

        //unfortunately, equality is nontrivial and therefore probably
        //is very slow, although points must be in counterclockwise fasion
        //the starting point
        //bool operator==(const Poly2& other) const {
        //    if (size() != other.size()) return false;
        //    size_t len = size();

        //    if (points[0] == other[0]) {
        //        //easy equality case
        //        size_t i = 0;
        //        bool eq = true;
        //        while (i < len && eq) {
        //            eq = eq && points[i] == other[i];
        //            i++;
        //        }
        //        return eq;
        //    }
        //    else {
        //        for (size_t j = 0; j < len; j++) {
        //            //check for alternate starting point
        //            if (points[0] == other[j]) {
        //                //hard equality case
        //                size_t i = 0;
        //                bool eq = true;
        //                while (i < len && eq) {
        //                    eq = eq && (points[i] == other.next(i + j - 1));
        //                    i++;
        //                }
        //                return eq;
        //            }
        //        }

        //        //no starting point found
        //        return false;
        //    }
        //}

        bool operator!= (const Poly2& other) const noexcept {
            return !(operator==(other));
        }

        Poly2& operator-=(const Vec& rhs) noexcept {
            auto len = size();
            for (size_t i = 0; i < len; i++) {
                points[i] -= rhs;
            }

            cent -= rhs;

            return *this;
        }

        Poly2 operator-(const Vec& rhs) const noexcept {
            auto len = size();
            Point newcent = cent - rhs;
            std::vector<Point> newpoints;
            newpoints.reserve(len);
            for (size_t i = 0; i < len; i++) {
                newpoints.push_back(points[i] - rhs);
            }
            return Poly2(newpoints, newcent);
        }

        Poly2& operator-=(const Normal_Vec& rhs) noexcept {
            auto len = size();
            for (size_t i = 0; i < len; i++) {
                points[i] -= rhs;
            }

            cent -= rhs;

            return *this;
        }

        Poly2 operator-(const Normal_Vec& rhs) const noexcept {
            auto len = size();
            Point newcent = cent - rhs;
            std::vector<Point> newpoints;
            newpoints.reserve(len);
            for (size_t i = 0; i < len; i++) {
                newpoints.push_back(points[i] - rhs);
            }
            return Poly2(newpoints, newcent);
        }

        Poly2& operator+=(const Vec& rhs) noexcept {
            auto len = size();
            for (size_t i = 0; i < len; i++) {
                points[i] += rhs;
            }

            cent += rhs;

            return *this;
        }

        Poly2 operator+(const Vec& rhs) const noexcept {
            auto len = size();
            Point newcent = cent + rhs;
            std::vector<Point> newpoints;
            newpoints.reserve(len);
            for (size_t i = 0; i < len; i++) {
                newpoints.push_back(points[i] + rhs);
            }
            return Poly2(newpoints, newcent);
        }

        Poly2& operator+=(const Normal_Vec& rhs) noexcept {
            auto len = size();
            for (size_t i = 0; i < len; i++) {
                points[i] += rhs;
            }

            cent += rhs;

            return *this;
        }

        Poly2 operator+(const Normal_Vec& rhs) const noexcept {
            auto len = size();
            Point newcent = cent + rhs;
            std::vector<Point> newpoints;
            newpoints.reserve(len);
            for (size_t i = 0; i < len; i++) {
                newpoints.push_back(points[i] + rhs);
            }
            return Poly2(newpoints, newcent);
        }

        T area() const noexcept {
            T a = 0.0;

            auto len = size();
            auto j = len - 1;
            for (auto i = 0; i < len; i++)
            { 
                a += (points[j].x + points[i].x) * (points[j].y - points[i].y);
                j = i;
            }
            return abs(a / static_cast<T>(2.0));
        }

        size_t size() const noexcept {
            return points.size();
        }

        Rect getAABB() const noexcept {
            T minx = points[0].x;
            T miny = points[0].y;
            T maxx = points[0].x;
            T maxy = points[0].y;
            auto len = size();
            for (size_t i = 1; i < size(); i++) {
                minx = min(minx, points[i].x);
                maxx = max(maxx, points[i].x);

                miny = min(miny, points[i].y);
                maxy = max(maxy, points[i].y);
            }
            return Rect(Point(minx, miny), Point(maxx, maxy));
        }

        template <typename other_T, typename other_SpaceType>
        operator Poly2<other_T, other_SpaceType>() const noexcept {
            Matrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            Poly2 first_transform = from.transformPoly(*this);

            //step 2: copy contents into new type container

            std::vector<Point2<other_T, other_SpaceType>> newpoints;
            auto len = size();
            newpoints.reserve(len);
            for (size_t i = 0; i < len; i++) {
                newpoints.push_back(Point(static_cast<other_T>(first_transform.points[i].x), static_cast<other_T>(first_transform.points[i].y)));
            }

            Poly2<other_T, other_SpaceType> second_transform(newpoints);

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return to.transformPoly(second_transform);
        }

        friend std::ostream& operator << (std::ostream& os, const Poly2<T, SpaceType>& it) {
            const auto space = SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Polygon[size = " << it.points.size() << "]{\n";
            for (size_t i = 0; i < it.points.size(); i++) {
                os << "(" << it.points.at(i).x << ", " << it.points.at(i).y << "),\n";
            }
            os << "}";
            return os;
        }

    private:

        //T signed_doubled_area() {
        //    int n = static_cast<int>(points.size());
        //    T area = static_cast<T>(0);
        //    for (int i = 0; i < n; i++) {
        //        area += points[i].x * (next(i).y - prev(i).y);
        //    }
        //    return area;
        //}

        //const Point& prev(const size_t i) const {
        //    return i == 0 ? points[size() - 1] : points[i - 1];
        //}

        //const Point& next(const size_t i) const {
        //    return i == size() - 1 ? points[0] : points[i + 1];
        //}

        friend class AffineMatrix<T, SpaceType>;

        std::vector<Point> points;

        Point cent;

        Point calc_centroid() const noexcept {
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

                cent.x += (x0 + x1) * A;
                cent.y += (y0 + y1) * A;
            }

            double x0 = points[len - 1].x;
            double y0 = points[len - 1].y;
            double x1 = points[0].x;
            double y1 = points[0].y;

            double A = (x0 * y1) - (x1 * y0);
            signedArea += A;

            cent.x += (x0 + x1) * A;
            cent.y += (y0 + y1) * A;

            signedArea *= 0.5;
            cent.x /= (6 * signedArea);
            cent.y /= (6 * signedArea);

            return cent;
        }

        //fast "copy" constructor that doesnt come with any of the invariant checking
        explicit Poly2(const std::vector<Point> &points, const Point &centroid) noexcept : points(points), cent(centroid) {}
    };
}

