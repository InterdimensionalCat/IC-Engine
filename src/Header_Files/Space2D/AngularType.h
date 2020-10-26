#pragma once
#include <ratio>
#include <iostream>
#include <numeric>

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
using AngType = AngularType<double, struct Ang, Ratio>;

using Radians = AngType<std::ratio<1, 1>>;
using Degrees = AngType<std::ratio<31415926535897932, 1800000000000000000>>;
using Percent = AngType<std::ratio<31415926535897932, 5000000000000000>>;

inline Radians operator"" _rad(const long double d) noexcept {
	return Radians(d);
}

inline Radians operator"" _pi_rad(const long double d) noexcept {
	return Radians(d * 3.1415926535897932);
}

inline Degrees operator"" _deg(const long double d) noexcept {
	return Degrees(d);
}

inline Percent operator"" _percent(const long double d) noexcept {
	return Percent(d);
}

inline Radians operator"" _rad(const unsigned long long d) noexcept {
	return Radians(static_cast<double>(d));
}

inline Radians operator"" _pi_rad(const unsigned long long d) noexcept {
	return Radians(static_cast<double>(d) * 3.1415926535897932);
}

inline Degrees operator"" _deg(const unsigned long long d) noexcept {
	return Degrees(static_cast<double>(d));
}

inline Percent operator"" _percent(const unsigned long long d) noexcept {
	return Percent(static_cast<double>(d));
}

inline std::ostream& operator << (std::ostream& os, const Radians& it) {
	double pie_ratio = (it / 180_deg).get();
	if (pie_ratio == 1) {
		os << "pi radians";
		return os;
	}

	if (pie_ratio == 0) {
		os << "0 radians";
		return os;
	}

	long precisison = 1000;

	long gcdnum = std::gcd((long)round(pie_ratio * precisison), precisison);

	double numerator = (pie_ratio * precisison) / (double)gcdnum;
	long denominator = precisison / gcdnum;

	if (abs(numerator - 1) < 1e-6) {
		os << "pi" << "/" << denominator << " radians";
		return os;
	}

	if (denominator == 1) {
		os << numerator << "pi radians";
		return os;
	}

	if (gcdnum == 1) {
		os << pie_ratio << "pi radians";
		return os;
	}

	os << numerator << "pi/" << denominator << " radians";
	return os;
}

inline std::ostream& operator << (std::ostream& os, const Degrees& it) {
	os << it.get() << " degrees";
	return os;
}

inline std::ostream& operator << (std::ostream& os, const Percent& it) {
	os << it.get() * 100.0 << "%";
	return os;
}

