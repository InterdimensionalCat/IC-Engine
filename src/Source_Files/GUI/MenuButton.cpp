#include "include.h"
#include "MenuButton.h"
#include "MenuState.h"

using namespace s2d;

MenuButton::MenuButton(const Point& center, const string& text, const string& font, const size_t& fontSize, std::shared_ptr<MenuState>& parent) : Button(Rectangle(0,0,1,1), 0.0f, Color(0,0,0,0), Color(0,0,0,0)), parent(parent) {

	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "fonts";
	filepath /= font;
	filepath += ".ttf";


	if (!buttonFont.loadFromFile(filepath.generic_u8string())) {
#ifdef _DEBUG
		throw TextureLoadException(font, filepath.generic_u8string());
#endif
	}
	option = Text(text, buttonFont);
	option.setCharacterSize((unsigned int)fontSize);
	option.setFillColor(Color(50, 50, 50));
	option.setOutlineColor(Color::Black);
	option.setOutlineThickness(5);
	option.setStyle(Text::Regular);
	Vector2f size = Vector2f(option.getGlobalBounds().width, option.getGlobalBounds().height);
	Vector2f topLeft = center.toSFMLVec<float>() - size / 2.0f;
	option.setPosition(center.toSFMLVec<float>());
	//option.setPosition(-size / 2.0f);
	Widget::bounds = Rectangle(Point(topLeft.x, topLeft.y), Dimension(size.x, size.y));
	auto cent = bounds.center();
	option.setOrigin(size / 2.0f);
	cent += Vec(0.0f, option.getGlobalBounds().height / 2);
	bounds.moveCenterTo(cent);
}

//selection functions
void MenuButton::onSelectEnd() {

}

void MenuButton::onSelectStart() {

}

//state functions
void MenuButton::unhovered() {
	Button::unhovered();
	option.setScale(1, 1);
	option.setFillColor(Color(50, 50, 50));
	option.setStyle(Text::Regular);
	auto cent = bounds.center();
	Widget::bounds = Rectangle(
		Point(option.getGlobalBounds().top, option.getGlobalBounds().left),
		Dimension(option.getGlobalBounds().width, option.getGlobalBounds().height)
	);
	bounds.moveCenterTo(cent);
}
void MenuButton::hovered() {
	Button::hovered();
	option.setScale(1.33f, 1.33f);
	option.setFillColor(Color(20, 20, 20));
	option.setStyle(Text::Bold);
	auto cent = bounds.center();
	Widget::bounds = Rectangle(
		Point(option.getGlobalBounds().top, option.getGlobalBounds().left),
		Dimension(option.getGlobalBounds().width, option.getGlobalBounds().height)
	);
	bounds.moveCenterTo(cent);
}
void MenuButton::selected() {
	Button::selected();
	parent->select(option.getString().toAnsiString());
}

//update functions
void MenuButton::draw(std::shared_ptr<Renderer>& renderer) {
	Widget::draw(renderer);
	renderer->window->draw(option, renderer->states);
#ifdef debug_mode
	if (instance->debug) {
		renderer->window->draw(bounds.makeDrawableSFMLRect(5.0, Color(0,0,0,0), Color(255, 0,0,255)), renderer->states);
	}
#endif
}
void MenuButton::updateListener(const float dt) {

}