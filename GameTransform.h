#pragma once
#include "Behavior.h"

class GameTransform :
	public Behavior
{
public:
	float getX() const { return pos.x; }
	float getY() const { return pos.y; }
	float getPrevX() const { return prevpos.x; }
	float getPrevY() const { return prevpos.y; }
	Vector2f getPos() const { return pos; }
	Vector2f getPrevPos() const { return prevpos; }
	void translate(const Vector2f trans);
	void setPos(const Vector2f newpos);
	void setPos(const float x, const float y);
	void start();
	void tick(InputHandle* input);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Vector2f forward() const;
	Vector2f up() const;
	Vector2f down() const;
	Vector2f back() const;

	bool updated();
	void setupdated();

private:
	Vector2f pos = Z_VEC;
	Vector2f prevpos = Z_VEC;

	Vector2f fwd = Vector2f(1, 0);
	Vector2f upvec = Vector2f(0, 1);

	bool upd = true;
};

