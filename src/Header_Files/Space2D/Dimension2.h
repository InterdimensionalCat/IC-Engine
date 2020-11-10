#pragma once
#include "SFML/Graphics.hpp"

namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

    class Dimension2 final
    {

    public:

        //defaults to width = 0, height = 0
        Dimension2() noexcept;

        explicit Dimension2(const float& x, const float& y) noexcept;

        //define a Dimension2 as the area between 2 points
        explicit Dimension2(const Point2& min, const Point2& max) noexcept;

        explicit Dimension2(const Point2& other) noexcept;

        explicit Dimension2(const Vec2& other) noexcept;

        const float& operator[] (const unsigned int i) const noexcept;

        float& operator[] (const unsigned int i) noexcept;

        bool operator==(const Dimension2& other) const noexcept;

        bool operator!=(const Dimension2& other) const noexcept;

        Dimension2& operator-=(const Dimension2& rhs) noexcept;

        Dimension2& operator-=(const Vec2& rhs) noexcept;

        Dimension2& operator-=(const NormalizedVec2& rhs) noexcept;

        Dimension2 operator-(const Dimension2& rhs) const noexcept;

        Dimension2 operator-(const Vec2& rhs) const noexcept;

        Dimension2 operator-(const NormalizedVec2& rhs) const noexcept;

        Dimension2& operator+=(const Dimension2& rhs) noexcept;

        Dimension2& operator+=(const Vec2& rhs) noexcept;

        Dimension2& operator+=(const NormalizedVec2& rhs) noexcept;

        Dimension2 operator+(const Dimension2& rhs) const noexcept;

        Dimension2 operator+(const Vec2& rhs) const noexcept;

        Dimension2 operator+(const NormalizedVec2& rhs) const noexcept;

        Dimension2& operator*=(const float& factor) noexcept;

        Dimension2 operator*(const float& factor) const noexcept;

        Dimension2& operator/=(const float& factor) noexcept;

        Dimension2 operator/(const float& factor) const noexcept;

        template <typename SFMLType = float>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }

        friend std::ostream& operator << (std::ostream& os, const Dimension2& it) {
            os << "Dimension2(" << it.x << ", " << it.y << ")";
            return os;
        }

        float x;
        float y;
    };
}



