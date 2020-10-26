#pragma once
#include "ActionState.h"
#include "Animation.h"


class Composite;

class PlayerAirborneState : public ActionState
{
public:
	PlayerAirborneState();

	virtual void init();

	void enter();

	void run(InputHandle* input);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void exit();

	mutable Animation anim;

	float airaccel = 10.0f * 60;
	float maxVelX = 13.0f * 60;

	GameTransform* transform;
	Composite* compIn;
};