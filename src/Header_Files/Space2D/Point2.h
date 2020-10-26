#pragma once
#include "Space2D.h"

#ifndef SFML_DISABLE
#include "SFML/Graphics.hpp"
#endif

namespace Space2D {
    template <typename T, typename SpaceType>
    class Point2 final
    {

    public:


        using Point = Point2 <T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;
        using Normal_Vec = NormalizedVec2<T, SpaceType>;
        using Matrix = AffineMatrix<T, SpaceType>;
        using Dimension = Dimension2<T, SpaceType>;


        //defaults to (0,0)
        Point2()  noexcept : x(0), y(0) {}

        explicit Point2(const T& x, const T& y) noexcept : x(x), y(y) {}

        //define a point as an offset from another point
        explicit Point2(const Point& base, const Vec& offset) noexcept : x(base.x + offset.x), y(base.y + offset.y) {}

        //define a point as an offset from another point
        explicit Point2(const Point& base, const Normal_Vec& offset) noexcept : x(base.x + offset.x), y(base.y + offset.y) {}

        const T& operator[] (const unsigned int i) const noexcept {
            return i == 0 ? x : y;
        }

        T& operator[] (const unsigned int i) noexcept {
            return i == 0 ? x : y;
        }

        bool operator==(const Point& other) const noexcept {
            return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
        }

        bool operator!= (const Point& other) const noexcept {
            return !(operator==(other));
        }

        Point& operator-=(const Point& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Point& operator-=(const Vec& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Point& operator-=(const Normal_Vec& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Point& operator-=(const Dimension& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Point operator-(const Point& rhs) const noexcept {
            return Point(x - rhs.x, y - rhs.y);
        }

        Point operator-(const Vec& rhs) const noexcept {
            return Point(x - rhs.x, y - rhs.y);
        }

        Point operator-(const Normal_Vec& rhs) const noexcept {
            return Point(x - rhs.x, y - rhs.y);
        }

        Point operator-(const Dimension& rhs) const noexcept {
            return Point(x - rhs.x, y - rhs.y);
        }

        Point& operator+=(const Point& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point& operator+=(const Vec& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point& operator+=(const Normal_Vec& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point& operator+=(const Dimension& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point operator+(const Point& rhs) const noexcept {
            return Point(x + rhs.x, y + rhs.y);
        }

        Point operator+(const Vec& rhs) const noexcept {
            return Point(x + rhs.x, y + rhs.y);
        }

        Point operator+(const Normal_Vec& rhs) const noexcept {
            return Point(x + rhs.x, y + rhs.y);
        }

        Point operator+(const Dimension& rhs) const noexcept {
            return Point(x + rhs.x, y + rhs.y);
        }

        Point& operator*=(const T& factor) noexcept {
            x *= factor;
            y *= factor;
            return *this;
        }

        Point operator*(const T& factor) const noexcept {
            return Point(x * factor, y * factor);
        }

        Point& operator/=(const T& factor) noexcept {
            x /= factor;
            y /= factor;
            return *this;
        }

        Point operator/(const T& factor) const noexcept {
            return Point(x / factor, y / factor);
        }

        template <typename other_T, typename other_SpaceType>
        operator Point2<other_T, other_SpaceType>() const noexcept {
            Matrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            Point first_transform = from.transformPoint(*this);

            //step 2: copy contents into new type container
            Point2<other_T, other_SpaceType> second_transform(static_cast<other_T>(first_transform.x), static_cast<other_T>(first_transform.y));

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return to.transformPoint(second_transform);
        }

#ifndef SFML_DISABLE
        //convert the point to an sf::Vector2<T> (T defaults to float)
        template <typename SFMLType = T>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }
#endif

        friend std::ostream& operator << (std::ostream& os, const Point2<T, SpaceType>& it) {
            const auto space = Space2D::SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Point (" << it.x << ", " << it.y << ")";
            return os;
        }

        static Point lerp(const Point& a, const Point& b, const T t) {
            return Point(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
        }

        T x;
        T y;
    };
}



