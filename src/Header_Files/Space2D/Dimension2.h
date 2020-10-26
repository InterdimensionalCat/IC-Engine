#pragma once
#include "Space2D.h"

#ifndef SFML_DISABLE
#include "SFML/Graphics.hpp"
#endif

namespace Space2D {
    template <typename T, typename SpaceType>
    class Dimension2 final
    {


        using Dimension = Dimension2<T, SpaceType>;
        using Point = Point2<T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;
        using Normal_Vec = NormalizedVec2<T, SpaceType>;
        using Matrix = AffineMatrix<T, SpaceType>;

    public:

        //defaults to width = 0, height = 0
        Dimension2()  noexcept : x(0), y(0) {}

        explicit Dimension2(const T& x, const T& y) noexcept : x(x), y(y) {}

        //define a dimension as the area between 2 points
        explicit Dimension2(const Point& min, const Point& max) noexcept : x(max.x - min.x), y(max.y - min.y) {}

        const T& operator[] (const unsigned int i) const noexcept {
            return i == 0 ? x : y;
        }

        T& operator[] (const unsigned int i) noexcept {
            return i == 0 ? x : y;
        }

        bool operator==(const Dimension& other) const noexcept {
            return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
        }

        bool operator!= (const Dimension& other) const noexcept {
            return !(operator==(other));
        }

        Dimension& operator-=(const Dimension& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Dimension& operator-=(const Vec& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Dimension& operator-=(const Normal_Vec& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Dimension operator-(const Dimension& rhs) const noexcept {
            return Dimension(x - rhs.x, y - rhs.y);
        }

        Dimension operator-(const Vec& rhs) const noexcept {
            return Dimension(x - rhs.x, y - rhs.y);
        }

        Dimension operator-(const Normal_Vec& rhs) const noexcept {
            return Dimension(x - rhs.x, y - rhs.y);
        }

        Dimension& operator+=(const Dimension& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Dimension& operator+=(const Vec& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Dimension& operator+=(const Normal_Vec& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Dimension operator+(const Dimension& rhs) const noexcept {
            return Dimension(x + rhs.x, y + rhs.y);
        }

        Dimension operator+(const Vec& rhs) const noexcept {
            return Dimension(x + rhs.x, y + rhs.y);
        }

        Dimension operator+(const Normal_Vec& rhs) const noexcept {
            return Dimension(x + rhs.x, y + rhs.y);
        }

        Dimension& operator*=(const T& factor) noexcept {
            x *= factor;
            y *= factor;
            return *this;
        }

        Dimension operator*(const T& factor) const noexcept {
            return Dimension(x * factor, y * factor);
        }

        Dimension& operator/=(const T& factor) noexcept {
            x /= factor;
            y /= factor;
            return *this;
        }

        Dimension operator/(const T& factor) const noexcept {
            return Dimension(x / factor, y / factor);
        }


        template <typename other_T, typename other_SpaceType>
        operator Dimension2<other_T, other_SpaceType>() const noexcept {
            Matrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            Dimension first_transform = from.transformDim(*this);

            //step 2: copy contents into new type container
            Dimension2<other_T, other_SpaceType> second_transform(static_cast<other_T>(first_transform.x), static_cast<other_T>(first_transform.y));

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return to.transformDim(second_transform);
        }


#ifndef SFML_DISABLE
        template <typename SFMLType = T>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }
#endif

        friend std::ostream& operator << (std::ostream& os, const Dimension& it) {
            const auto space = Space2D::SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Dimension (" << it.x << ", " << it.y << ")";
            return os;
        }

        T x;
        T y;
    };
}



