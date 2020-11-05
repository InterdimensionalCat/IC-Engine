#pragma once
#include <ratio>
#include <iostream>
#include <numeric>
#include <cmath>

/*
  Defines the 3 "angular types"; degrees, radians, and percent
  This allowes for an angle value to be expressed in any of these 3
  ways, and each type implicity converts to the others so that you
  dont have to worry about which one a particular function takes

  NOTE: percent is defined OpenGL style: 1.0 == 100 percent
  since this is more helpful mathematically (and is what I am used to)
  however, 1.0 percent will print as "100%" for clarity
*/

template<typename T, typename Tag, typename Ratio>
class AngularType

{
public:
	AngularType() noexcept : value(0) {}
	explicit AngularType(const T& value) noexcept : value(value) {}
	explicit AngularType(const long double& value) noexcept : value(static_cast<T>(value)) {}
	T& get() noexcept { return value; }
	const T& get() const noexcept { return value; }


	template <typename OtherRatio>
	operator AngularType<T, Tag, OtherRatio>() const {

		return  AngularType<T, Tag, OtherRatio>(get() * Ratio::num / Ratio::den * OtherRatio::den / OtherRatio::num);
	}

	using Angular = AngularType<T, Tag, Ratio>;

	bool operator==(const Angular& other) const noexcept {
		return abs(value - other.get()) < 1e-6;
	}

	bool operator!= (const Angular& other) const noexcept {
		return !(operator==(other));
	}



	Angular& operator-=(const Angular& rhs) noexcept {
		value -= rhs.get();
		return *this;
	}

	Angular operator-(const Angular& rhs) const noexcept {
		return Angular(value - rhs.get());
	}


	Angular& operator+=(const Angular& rhs) noexcept {
		value += rhs.get();
		return *this;
	}

	Angular operator+(const Angular& rhs) const noexcept {
		return Angular(value + rhs.get());
	}


	Angular& operator*=(const Angular& rhs) noexcept {
		value *= rhs.get();
		return *this;
	}

	Angular& operator*=(const T& rhs) noexcept {
		value *= rhs;
		return *this;
	}


	Angular operator*(const Angular& rhs) const noexcept {
		return Angular(value * rhs.get());
	}

	Angular operator*(const T& rhs) const noexcept {
		return Angular(value * rhs);
	}

	Angular& operator/=(const Angular& rhs) noexcept {
		value /= rhs.get();
		return *this;
	}

	Angular& operator/=(const T& rhs) noexcept {
		value /= rhs;
		return *this;
	}


	Angular operator/(const Angular& rhs) const noexcept {
		return Angular(value / rhs.get());
	}

	Angular operator/(const T& rhs) const noexcept {
		return Angular(value / rhs);
	}

	Angular operator-() const noexcept {
		return Angular(-value);
	}

	Angular operator+() const noexcept {
		return Angular(+value);
	}

	Angular operator%(const Angular& rhs) const noexcept {
		return Angular(value % rhs.get());
	}

	Angular& operator%=(const Angular& rhs) const noexcept {
		value %= rhs.get();
		return *this;
	}

private:
	T value;
};

template<typename Ratio>
using AngType = AngularType<float, struct Ang, Ratio>;

using Radians = AngType<std::ratio<1, 1>>;
using Degrees = AngType<std::ratio<31415926535897932, 1800000000000000000>>;
using Percent = AngType<std::ratio<31415926535897932, 5000000000000000>>;

Radians operator"" _rad(const long double d) noexcept;

Radians operator"" _pi_rad(const long double d) noexcept;

Degrees operator"" _deg(const long double d) noexcept;

Percent operator"" _percent(const long double d) noexcept;

Radians operator"" _rad(const unsigned long long d) noexcept;

Radians operator"" _pi_rad(const unsigned long long d) noexcept;

Degrees operator"" _deg(const unsigned long long d) noexcept;

Percent operator"" _percent(const unsigned long long d) noexcept;

std::ostream& operator << (std::ostream& os, const Radians& it);

std::ostream& operator << (std::ostream& os, const Degrees& it);

std::ostream& operator << (std::ostream& os, const Percent& it);

