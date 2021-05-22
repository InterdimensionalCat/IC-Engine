#pragma once
/*
various helper functions for
SFML to work nicely with the engine
*/

//standard linear interpolation
float glerp(const float a, const float b, const float t);

// "2D linear interpolation"; just interprets each component of the vector individually
Vector2f glerp(const sf::Vector2f& a, const sf::Vector2f& b, const float t);

//prints sf::Vector2f type
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2f& rhs) {
	os << "sf::Vector2f(" << rhs.x << "," << rhs.y << ")";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2i& rhs) {
	os << "sf::Vector2i(" << rhs.x << "," << rhs.y << ")";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2u& rhs) {
	os << "sf::Vector2u(" << rhs.x << "," << rhs.y << ")";
	return os;
}
