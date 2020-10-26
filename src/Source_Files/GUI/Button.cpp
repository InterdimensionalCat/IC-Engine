#include "include.h"
#include "Button.h"

Button::Button() {}

Button::Button(const string &text, const string &font, const Vector2f &pos) {

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
	option.setCharacterSize(100);
	option.setFillColor(Color(50, 50, 50));
	option.setOutlineColor(Color::Black);
	option.setOutlineThickness(5);
	option.setStyle(Text::Regular);
	option.setPosition(pos);
	hitbox = option.getGlobalBounds();
	option.setPosition(pos);
	option.setOrigin(Vector2f(hitbox.width, hitbox.height) / 2.0f);
	hitbox = option.getGlobalBounds();
}

void Button::hovered() {
	//visual changes only
	option.setScale(1.33, 1.33);
	option.setFillColor(Color(20, 20, 20));
	option.setStyle(Text::Bold);
	hitbox = option.getGlobalBounds();
}

void Button::unhovered() {
	//visual changes only
	option.setScale(1, 1);
	option.setFillColor(Color(50, 50, 50));
	option.setStyle(Text::Regular);
	hitbox = option.getGlobalBounds();
}

void Button::selected() {
	//play a sound?

}

void Button::draw(RenderTarget& target, RenderStates states) const {
	target.draw(option, states);
}