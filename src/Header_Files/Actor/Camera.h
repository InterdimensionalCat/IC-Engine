#pragma once
#include "Actor.h"

class Camera : public Actor
{
public:
	string getTag() const { return "Camera"; }
	virtual void start();
	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& input);

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

