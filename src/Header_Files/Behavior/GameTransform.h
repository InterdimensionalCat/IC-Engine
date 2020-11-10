#pragma once
#include "Behavior.h"
//GameTransform.h
/*
  Behavior used by all actors representing the position and
  other transformable attributes about the Actor, the position
  should be set to the center of the object, but this is not
  enforced
*/

class GameTransform :
	public Behavior
{
public:
	//getters for the X and Y coordinates
	float getX() const { return pos.x; }
	float getY() const { return pos.y; }
	float getPrevX() const { return prevpos.x; }
	float getPrevY() const { return prevpos.y; }

	//getters that give a Point containing both the X and Y position
	s2d::Point getPos() const { return pos; }
	s2d::Point getPrevPos() const { return prevpos; }

	//moves the transform reletive to its current position, DO NOT CALL THIS if the object in question
	//has a component that manages the transform for you
	void translate(const s2d::Vec& trans);

	//reset the position to some Point
	void setPos(const s2d::Point& newpos);
	void setPos(const float x, const float y);

	void start();
	void tick(InputHandle* input);
	void draw(Renderer* renderer);

	//normal vectors representing the cardinal directions for this transform
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

