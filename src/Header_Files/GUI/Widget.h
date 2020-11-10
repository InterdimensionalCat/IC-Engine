#pragma once
#include "EventListener.h"
//Widget.h
/*
  abstract class for creating GUI elements
*/
class Widget : public EventListener
{

public:
	Widget(const s2d::Point& pos, const s2d::Dimension& dim, float border_size = 0.0f, const sf::Color& content_color = Color(0, 0, 0, 255), const sf::Color& border_color = Color(0, 0, 0, 0));

	Widget(const s2d::Rectangle& bounds, float border_size = 0.0f, const sf::Color& content_color = Color(0, 0, 0, 255), const sf::Color& border_color = Color(0, 0, 0, 0));

	virtual void draw(Renderer* renderer);

	//bounds do not include border
	s2d::Rectangle bounds;
	sf::Color border_color = Color(0, 0, 0, 255);
	sf::Color content_color = Color(0, 0, 0, 0);
	float border_size;
};