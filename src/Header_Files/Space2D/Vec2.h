#pragma once
#include "Space2D.h"

#ifndef SFML_DISABLE
#include "SFML/Graphics.hpp"
#endif

//    Sp::Vec translation;

namespace Space2D {
    template <typename T, typename SpaceType>
    class Vec2 final
    {

    public:

		using Vec = Vec2<T, SpaceType>;
		using Normal_Vec = NormalizedVec2<T, SpaceType>;
		using Point = Point2<T, SpaceType>;
		using Matrix = AffineMatrix<T, SpaceType>;

		//defaults to (0,0)
        Vec2()  noexcept : x(0), y(0) {}

        explicit Vec2(const T& x, const T& y) noexcept : x(x), y(y) {}

		//define a vector as the distance from two points in the direction from start to end
		explicit Vec2(const Point& start, const Point& end) noexcept : x(end.x - start.x), y(end.y - start.y) {}

		//construct a vector from a normal vector
		Vec2(const Normal_Vec& vec) noexcept : x(vec.x), y(vec.y) {}

        const T& operator[] (const unsigned int i) const noexcept {
            return i == 0 ? x : y;
        }

		T& operator[] (const unsigned int i) noexcept {
			return i == 0 ? x : y;
		}

		bool operator==(const Vec& other) const noexcept {
			return (std::abs(x - other.x) < 1e-6) && (std::abs(y - other.y) < 1e-6);
		}

		bool operator!= (const Vec& other) const noexcept {
			return !(operator==(other));
		}

		Vec& operator-=(const Vec& rhs) noexcept {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vec& operator-=(const Normal_Vec& rhs) noexcept {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vec operator-(const Vec& rhs) const noexcept {
			return Vec(x - rhs.x, y - rhs.y);
		}

		Vec operator-(const Normal_Vec& rhs) const noexcept {
			return Vec(x - rhs.x, y - rhs.y);
		}

		Vec& operator+=(const Vec& rhs) noexcept {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vec& operator+=(const Normal_Vec& rhs) noexcept {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vec operator+(const Vec& rhs) const noexcept {
			return Vec(x + rhs.x, y + rhs.y);
		}

		Vec operator+(const Normal_Vec& rhs) const noexcept {
			return Vec(x + rhs.x, y + rhs.y);
		}

		Vec& operator*=(const T& factor) noexcept {
			x *= factor;
			y *= factor;
			return *this;
		}

		Vec& operator*=(const Scalar<T, SpaceType>& factor) noexcept {
			x *= factor.value;
			y *= factor.value;
			return *this;
		}

		Vec operator*(const T& factor) const noexcept {
			return Vec(x * factor, y * factor);
		}

		T Dot(const Vec& other) const noexcept {
			return x * other.x + y * other.y;
		}

		T Dot(const Normal_Vec& other) const noexcept {
			return x * other.x + y * other.y;
		}

		Normal_Vec Normalize() const {
			return Normal_Vec(x, y);
		}

		T Mag() const noexcept {
			return std::sqrt(x * x + y * y);
		}

		T MagSquared() const noexcept {
			return x * x + y * y;
		}

		bool perp(const Vec& other) const noexcept {
			return std::abs(Dot(other)) < 1e-6;
		}

		bool perp(const Normal_Vec& other) const noexcept {
			return std::abs(Dot(other)) < 1e-6;
		}

		//unit normal rule: (x, y) -> (y, -x)
		Normal_Vec unitNormal() const noexcept {
			return Normal_Vec(this->y, -this->x);
		}


		template <typename other_T, typename other_SpaceType>
		operator Vec2<other_T, other_SpaceType>() const noexcept {
			Matrix from = SpaceType::transform_ratio.getInverse();

			//step 1: apply inverse of the reletive space transform the object is in
			Vec first_transform = from.transformVec(*this);

			//step 2: copy contents into new type container
			Vec2<other_T, other_SpaceType> second_transform(static_cast<other_T>(first_transform.x), static_cast<other_T>(first_transform.y));

			AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

			//apply the reletive space transform of the new space
			return to.transformVec(second_transform);
		}


#ifndef SFML_DISABLE
		template <typename SFMLType = T>
		sf::Vector2<SFMLType> toSFMLVec() const noexcept {
			return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
		}
#endif

		friend std::ostream& operator << (std::ostream& os, const Vec& it) {
			const auto space = SpaceTypeNameMap<SpaceType>::name;
			os << space << "::Vector(" << it.x << ", " << it.y << ")";
			return os;
		}

		static Vec lerp(const Vec& a, const Vec& b, const T t) {
			return Vec(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
		}

         T x;
         T y;
    };
}


