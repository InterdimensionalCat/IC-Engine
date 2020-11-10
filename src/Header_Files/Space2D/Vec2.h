#pragma once
#include "SFML/Graphics.hpp"

//Sp::Vec translation;
namespace Space2D {

	class Dimension2;
	class Vec2;
	class Point2;
	class Poly2;
	class NormalizedVec2;
	class Rect2;

    class Vec2 final
    {

    public:


		//defaults to (0,0)
		Vec2()  noexcept;

		explicit Vec2(const float& x, const float& y) noexcept;

		//define a vector as the distance from two points in the direction from start to end
		explicit Vec2(const Point2& start, const Point2& end) noexcept;

		//construct a vector from a normal vector
		explicit Vec2(const NormalizedVec2& vec) noexcept;

		const float& operator[] (const unsigned int i) const noexcept;

		float& operator[] (const unsigned int i) noexcept;

		Vec2 operator- () const noexcept;

		bool operator==(const Vec2& other) const noexcept;

		bool operator!= (const Vec2& other) const noexcept;

		Vec2& operator-=(const Vec2& rhs) noexcept;

		Vec2& operator-=(const NormalizedVec2& rhs) noexcept;

		Vec2 operator-(const Vec2& rhs) const noexcept;

		Vec2 operator-(const NormalizedVec2& rhs) const noexcept;

		Vec2& operator+=(const Vec2& rhs) noexcept;

		Vec2& operator+=(const NormalizedVec2& rhs) noexcept;

		Vec2 operator+(const Vec2& rhs) const noexcept;

		Vec2 operator+(const NormalizedVec2& rhs) const noexcept;

		Vec2& operator*=(const float& factor) noexcept;

		Vec2 operator*(const float& factor) const noexcept;

		float Dot(const Vec2& other) const noexcept;

		float Dot(const NormalizedVec2& other) const noexcept;

		NormalizedVec2 Normalize() const;

		float Mag() const noexcept;

		float MagSquared() const noexcept;

		bool perp(const Vec2& other) const noexcept;

		bool perp(const NormalizedVec2& other) const noexcept;

		//unit normal rule: (x, y) -> (y, -x)
		NormalVec unitNormal() const noexcept;


		template <typename SFMLType = float>
		sf::Vector2<SFMLType> toSFMLVec() const noexcept {
			return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
		}

		friend std::ostream& operator << (std::ostream& os, const Vec2& it) {
			os << "Vector(" << it.x << ", " << it.y << ")";
			return os;
		}

		float x;
		float y;
    };
}


