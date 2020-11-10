#include "include.h"
#include "widget.h"

using namespace s2d;

Widget::Widget(const Point& pos, const Dimension& dim, float border_size, const sf::Color& content_color, const sf::Color& border_color)
	: bounds(pos, dim), border_size(border_size), content_color(content_color), border_color(border_color) {
}

Widget::Widget(const Rectangle& bounds, float border_size, const sf::Color& content_color, const sf::Color& border_color)
	: bounds(bounds), border_size(border_size), content_color(content_color), border_color(border_color) {
}

void Widget::draw(Renderer* renderer) {
	auto target = renderer->window.get();
	target->draw(bounds.makeDrawableSFMLRect(border_size, content_color, border_color), renderer->states);
}