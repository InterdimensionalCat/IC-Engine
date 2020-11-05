#include "include.h"
#include "AngularType.h"

Radians operator"" _rad(const long double d) noexcept {
	return Radians(d);
}

Radians operator"" _pi_rad(const long double d) noexcept {
	return Radians(d * 3.1415926535897932);
}

Degrees operator"" _deg(const long double d) noexcept {
	return Degrees(d);
}

Percent operator"" _percent(const long double d) noexcept {
	return Percent(d);
}

Radians operator"" _rad(const unsigned long long d) noexcept {
	return Radians(static_cast<long double>(d));
}

Radians operator"" _pi_rad(const unsigned long long d) noexcept {
	return Radians(static_cast<long double>(d) * 3.1415926535897932);
}

Degrees operator"" _deg(const unsigned long long d) noexcept {
	return Degrees(static_cast<long double>(d));
}

Percent operator"" _percent(const unsigned long long d) noexcept {
	return Percent(static_cast<long double>(d));
}

std::ostream& operator << (std::ostream& os, const Radians& it) {
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

std::ostream& operator << (std::ostream& os, const Degrees& it) {
	os << it.get() << " degrees";
	return os;
}

std::ostream& operator << (std::ostream& os, const Percent& it) {
	os << it.get() * 100.0 << "%";
	return os;
}