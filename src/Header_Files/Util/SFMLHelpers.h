#pragma once
/*
various helper functions for
SFML to work nicely with the engine
*/

//standard linear interpolation
float lerp(const float a, const float b, const float t);

// "2D linear interpolation; just interprets each component of the vector individually"
Vector2f lerp(const Vector2f& a, const Vector2f& b, const float t);

//prints sf::Vector2f type
std::ostream& operator<<(std::ostream& os, const Vector2f& rhs);

