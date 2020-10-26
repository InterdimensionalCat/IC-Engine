#pragma once
#include "Space2D.h"

#ifndef SFML_DISABLE
#include "SFML/Graphics.hpp"
#endif

namespace Space2D {
    template <typename T, typename SpaceType>
    class NormalizedVec2 final
    {

    public:

        using Matrix = AffineMatrix<T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;

        explicit NormalizedVec2(const T& x, const T& y) : x(x / std::sqrt(x * x + y * y)), y(y / std::sqrt(x * x + y * y)) {}

        //constructor from radian angle value
        explicit NormalizedVec2(const Radians radians) noexcept : x(static_cast<T>(cos(radians.get()))), y(static_cast<T>(sin(radians.get()))) {}

        //explicit NormalizedVec2(const Degrees degrees) noexcept : NormalizedVec2((Radians)degrees) {}


        const T& operator[] (const unsigned int i) const {
            return i == 0 ? x : y;
        }

        bool operator==(const NormalizedVec2& other) const noexcept {
            return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
        }

        bool operator!= (const NormalizedVec2& other) const noexcept {
            return !(operator==(other));
        }

        Vec operator-(const NormalizedVec2& rhs) const noexcept {
            return Vec(x - rhs.x, y - rhs.y);
        }

        Vec operator-(const Vec& rhs) const noexcept {
            return Vec(x - rhs.x, y - rhs.y);
        }

        Vec operator+(const Vec& rhs) const noexcept {
            return Vec(x + rhs.x, y + rhs.y);
        }

        Vec operator+(const NormalizedVec2& rhs) const noexcept {
            return Vec(x + rhs.x, y + rhs.y);
        }

        Vec operator*(const T& factor) const noexcept {
            return Vec(x * factor, y * factor);
        }

        T Dot(const Vec& other) const noexcept {
            return x * other.x + y * other.y;
        }

        T Dot(const NormalizedVec2& other) const noexcept {
            return x * other.x + y * other.y;
        }

        Radians angleOf() const noexcept {
            return Radians(acos(static_cast<double>(x)));
        }

        bool perp(const Vec& other) const noexcept {
            return std::abs(Dot(other)) < 1e-6;
        }

        bool perp(const NormalizedVec2& other) const noexcept {
            return std::abs(Dot(other)) < 1e-6;
        }

        template <typename other_T, typename other_SpaceType>
        operator NormalizedVec2<other_T, other_SpaceType>() const noexcept {
            Matrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            NormalizedVec2 first_transform = from.transformNormalVec(*this);

            //step 2: copy contents into new type container
            NormalizedVec2<other_T, other_SpaceType> second_transform(static_cast<other_T>(first_transform.x), static_cast<other_T>(first_transform.y));

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return to.transformNormalVec(second_transform);
        }

#ifndef SFML_DISABLE
        template <typename SFMLType = T>
        sf::Vector2<SFMLType> toSFMLVec() const noexcept {
            return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
        }
#endif

        friend std::ostream& operator << (std::ostream& os, const NormalizedVec2& it) {
            const auto space = SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Normal (" << it.x << ", " << it.y << ")";
            return os;
        }

        const T x;
        const T y;
    };
}



