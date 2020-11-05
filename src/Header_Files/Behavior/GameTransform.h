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
	s2d::Point getPos() const { return pos; }
	s2d::Point getPrevPos() const { return prevpos; }
	void translate(const s2d::Vec& trans);
	void setPos(const s2d::Point& newpos);
	void setPos(const float x, const float y);
	void start();
	void tick(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	s2d::NormalVec forward() const;
	s2d::NormalVec up() const;
	s2d::NormalVec down() const;
	s2d::NormalVec back() const;

private:
	s2d::Point pos;
	s2d::Point prevpos;

	s2d::NormalVec fwd = s2d::NormalVec(0_deg);
	s2d::NormalVec upvec = s2d::NormalVec(-90_deg);
};

