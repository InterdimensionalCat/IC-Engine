#pragma once
#include "Space2D.h"
#include <vector>
#include <algorithm>

namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

    class Poly2 final
    {

    public:

        //defaults to a single-point polygon with centroid (0,0)
        Poly2() noexcept;

        //construct a polygon directly from a set of points
        explicit Poly2(const std::vector<Point>& points) noexcept;

        //construct a polygon from a set of points ranging from zero to one
        //and define their scaled AABB dimensions
        explicit Poly2(const std::vector<Point2>& points0_to_1, const Rect2& quad_dim) noexcept;

        explicit Poly2(const Rect2& quad_dim) noexcept;

        const Point2& operator[] (const size_t i) const;


        Point2* begin();
        const Point2* begin() const;
        Point2* end();
        const Point2* end() const;

        const Point2& centroid() const;

        void setCenter(const Point2& newcenter);

        NormalizedVec2 normal(const unsigned int i) const;


        bool operator==(const Poly2& other) const;

        bool operator!= (const Poly2& other) const noexcept;

        Poly2& operator-=(const Vec2& rhs) noexcept;

        Poly2 operator-(const Vec2& rhs) const noexcept;

        Poly2& operator-=(const NormalizedVec2& rhs) noexcept;

        Poly2 operator-(const NormalizedVec2& rhs) const noexcept;

        Poly2& operator+=(const Vec2& rhs) noexcept;

        Poly2 operator+(const Vec2& rhs) const noexcept;

        Poly2& operator+=(const NormalizedVec2& rhs) noexcept;

        Poly2 operator+(const NormalizedVec2& rhs) const noexcept;

        float area() const noexcept;

        size_t size() const noexcept;

        Rect2 getAABB() const noexcept;

        friend std::ostream& operator << (std::ostream& os, const Poly2& it) {
            os << "Polygon[size = " << it.points.size() << "]{\n";
            for (size_t i = 0; i < it.points.size(); i++) {
                os << "(" << it.points.at(i).x << ", " << it.points.at(i).y << "),\n";
            }
            os << "}";
            return os;
        }

        sf::ConvexShape getDrawableSFMLPolygon(const float bordersize = 0.0f, const sf::Color interior_color = sf::Color(0, 0, 0, 0), const sf::Color border_color = sf::Color(0, 0, 0, 0)) const {
            sf::ConvexShape newshape;
            newshape.setOutlineThickness(bordersize);
            newshape.setOutlineColor(border_color);
            newshape.setFillColor(interior_color);
            newshape.setPointCount(points.size());
            for (size_t i = 0; i < points.size(); i++) {
                sf::Vector2f vec((float)points[i].x, (float)points[i].y);
                newshape.setPoint(i, vec);
            }
            return newshape;
        }

    private:

        friend class AffineMatrix;

        std::vector<Point> points;

        Point2 cent;

        Point2 calc_centroid() const noexcept;

        explicit Poly2(const std::vector<Point>& points, const Point2& centroid) noexcept;
    };
}

