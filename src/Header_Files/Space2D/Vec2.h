#pragma once
#include "SFML/Graphics.hpp"
#include "S2DIterator.h"


namespace Space2D {

	template<typename T>
	class Point2;
	template<typename T>
	class NormVec2;

	template<typename T>
    class Vec2
    {

    public:

		constexpr Vec2() noexcept : x(), y() {}
		constexpr explicit Vec2(const T& x, const T& y) noexcept : x(x), y(y) {}
		constexpr explicit Vec2(const Point2<T>& other) noexcept : Vec2(other.x, other.y) {}
		constexpr explicit Vec2(const Point2<T>& start, const Point2<T>& end) noexcept : Vec2(end.x - start.x, end.y - start.y) {}


		Vec2 operator-() const noexcept {
			return Vec2<T>(-x, -y);
		}

		const T& operator[] (const size_t i) const noexcept {
			return i == 0 ? x : y;
		}
		T& operator[] (const size_t i) noexcept {

			return i == 0 ? x : y;
		}

		const size_t numVals() const {
			return 2;
		}

		S2D_ITR_DEF(Vec2)

		auto operator<=>(const Vec2&) const noexcept = default;
		bool operator==(const Vec2& other) const noexcept {
			return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
		}

		T Mag() const noexcept {
			return std::sqrt(x * x + y * y);
		}

		T MagSquared() const noexcept {
			return x * x + y * y;
		}


		NormVec2<T> Normalize() const {
			return NormVec2<T>(x, y);
		}

		//unit normal rule: (x, y) -> (y, -x)
		NormVec2<T> unitNormal() const {
			return NormVec2<T>(y, -x);
		}


		template <typename SFMLType = float>
		sf::Vector2<SFMLType> toSFMLVec() const noexcept {
			return sf::Vector2<SFMLType>(static_cast<SFMLType>(this->x), static_cast<SFMLType>(this->y));
		}

		friend std::ostream& operator << (std::ostream& os, const Vec2<T>& it) {
			std::string typname = typeid(T).name();
			std::string::size_type i = typname.find("struct");
			if (i != std::string::npos) {
				typname.erase(i, 7);
			}
			i = typname.find("class");
			if (i != std::string::npos) {
				typname.erase(i, 6);
			}
			os << "Vec2<" << typname << ">(" << it.x << ", " << it.y << ")";
			return os;
		}

		T x;
		T y;
    };
}


