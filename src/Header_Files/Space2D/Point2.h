#pragma once
#include "SFML/Graphics.hpp"

namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

    class Point2 final
    {

    public:


        //defaults to (0,0)
        Point2() noexcept;

        //construct from an x and y float
        explicit Point2(const float& x, const float& y) noexcept;

        //construct directly from a vector
        explicit Point2(const Vec2& other) noexcept;

        //define a point as an offset from another point
        explicit Point2(const Point2& base, const Vec2& offset) noexcept;

        //define a point as an offset from another point
        explicit Point2(const Point2& base, const NormalizedVec2& offset) noexcept;

        const float& operator[] (const unsigned int i) const noexcept;

        float& operator[] (const unsigned int i) noexcept;

        bool operator==(const Point2& other) const noexcept;

        bool operator!= (const Point2& other) const noexcept;

        Point& operator-=(const Point2& rhs) noexcept;

        Point& operator-=(const Vec2& rhs) noexcept;

        Point& operator-=(const NormalizedVec2& rhs) noexcept;

        Point& operator-=(const Dimension2& rhs) noexcept;

        Point operator-(const Point2& rhs) const noexcept;

        Point operator-(const Vec2& rhs) const noexcept;

        Point operator-(const NormalizedVec2& rhs) const noexcept;

        Point operator-(const Dimension2& rhs) const noexcept;

        Point& operator+=(const Point2& rhs) noexcept;

        Point& operator+=(const Vec2& rhs) noexcept;

        Point& operator+=(const NormalizedVec2& rhs) noexcept;

        Point& operator+=(const Dimension2& rhs) noexcept;

        Point operator+(const Point2& rhs) const noexcept;

        Point operator+(const Vec2& rhs) const noexcept;

        Point operator+(const NormalizedVec2& rhs) const noexcept;

        Point operator+(const Dimension2& rhs) const noexcept;

        Point& operator*=(const float& factor) noexcept;

        Point operator*(const float& factor) const noexcept;

        Point& operator/=(const float& factor) noexcept;

        Point operator/(const float& factor) const noexcept;

        //convert the point to an sf::Vector2<T> (T defaults to float)
        template <typename SFMLType = float>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }

        friend std::ostream& operator << (std::ostream& os, const Point2& it) {
            os  << "Point(" << it.x << ", " << it.y << ")";
            return os;
        }

        float x;
        float y;
    };
}



