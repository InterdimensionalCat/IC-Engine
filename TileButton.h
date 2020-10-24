#pragma once
#include <SFML\Graphics.hpp>
class TileButton :
	public Drawable
{
public:
	TileButton(const Vector2f &pos);
	void hovered();
	void unhovered();
	void selected();
	void unselected();
	void draw(RenderTarget& target, RenderStates states) const;
	void move(Vector2f newpos);
	Vector2f pos;
	float radius = 2.0f;
	CircleShape drawshape;
};

