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
	s2d::GameUnits::Point getPos() const { return pos; }
	s2d::GameUnits::Point getPrevPos() const { return prevpos; }
	void translate(const s2d::GameUnits::Vec trans);
	void setPos(const s2d::GameUnits::Point newpos);
	void setPos(const float x, const float y);
	void start();
	void tick(InputHandle* input);
	void draw(Renderer* renderer);

	s2d::GameUnits::Vec forward() const;
	s2d::GameUnits::Vec up() const;
	s2d::GameUnits::Vec down() const;
	s2d::GameUnits::Vec back() const;

private:
	s2d::GameUnits::Point pos;
	s2d::GameUnits::Point prevpos;

	s2d::GameUnits::Vec fwd = s2d::GameUnits::Vec(1, 0);
	s2d::GameUnits::Vec upvec = s2d::GameUnits::Vec(0, 1);
};

