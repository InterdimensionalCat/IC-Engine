#pragma once
#include "Actor.h"

class GameTransform;

class Camera : public Actor
{
public:
	string getTag() const { return "Camera"; }
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void move(Vector2f trans);
	void setPos(Vector2f newpos);
	void rotate(const float &rotation);
	void zoom(const float &scale);
	void reset();
	void reset(Vector2f pos);

private:
	GameTransform* transform;

	float rotation;
	float prevrotation;

	float scale;
	float prevscale;
};

