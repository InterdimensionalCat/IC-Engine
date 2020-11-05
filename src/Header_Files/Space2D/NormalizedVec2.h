#pragma once
#include "SFML/Graphics.hpp"

namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

    class NormalizedVec2 final
    {

    public:

        explicit NormalizedVec2(const float& x, const float& y);

        //constructor from radian angle value
        explicit NormalizedVec2(const Radians radians) noexcept;


        const float& operator[] (const unsigned int i) const;

        NormalizedVec2 operator-() const noexcept;

        bool operator==(const NormalizedVec2& other) const noexcept;

        bool operator!= (const NormalizedVec2& other) const noexcept;

        Vec operator-(const NormalizedVec2& rhs) const noexcept;

        Vec operator-(const Vec2& rhs) const noexcept;

        Vec operator+(const Vec2& rhs) const noexcept;

        Vec operator+(const NormalizedVec2& rhs) const noexcept;

        Vec operator*(const float& factor) const noexcept;

        float Dot(const Vec2& other) const noexcept;

        float Dot(const NormalizedVec2& other) const noexcept;

        Radians angleOf() const noexcept;

        bool perp(const Vec2& other) const noexcept;

        bool perp(const NormalizedVec2& other) const noexcept;

        template <typename SFMLType = T>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }

        friend std::ostream& operator << (std::ostream& os, const NormalizedVec2& it) {
            os << "Normal (" << it.x << ", " << it.y << ")";
            return os;
        }

        float x;
        float y;
    };
}



