#pragma once
#include "Actor.h"

class Camera : public Actor
{
public:
	string getTag() const { return "Camera"; }
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);

	void move(s2d::GameUnits::Vec trans);
	void setPos(s2d::GameUnits::Point newpos);
	void rotate(const Radians &rotation);
	void zoom(const float &scale);
	void reset();
	void reset(s2d::GameUnits::Point pos);
	void update();

private:
	s2d::PixelUnits::Point pos;
	s2d::PixelUnits::Point prevpos;

	Radians rotation;
	Radians prevrotation;

	float scale;
	float prevscale;
};

