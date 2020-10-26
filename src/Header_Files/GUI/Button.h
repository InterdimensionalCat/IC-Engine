#pragma once

//button represented by text
class Button :
	public Drawable
{
public:
	Button();
	Button(const string &text, const string &font, const Vector2f &pos);
	void hovered();
	void unhovered();
	void selected();
	void draw(RenderTarget& target, RenderStates states) const;

	FloatRect hitbox;
	Text option;
	Font buttonFont;
};
