#pragma once
#include "Actor.h"
//Camera.h
/*
  The camrea object is responsible for moving the view of the window around and otherwise transforming it
*/

class Camera : public Actor
{
public:
	string getTag() const { return "Camera"; }
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);

	void move(const s2d::Vec& trans);
	void setPos(const s2d::Point& newpos);
	void rotate(const Radians &rotation);
	void zoom(const float &scale);
	void reset();
	void reset(s2d::Point pos);
	void update();

private:
	s2d::Point pos;
	s2d::Point prevpos;

	Radians rotation;
	Radians prevrotation;

	float scale;
	float prevscale;
};

