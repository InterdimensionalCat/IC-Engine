#pragma once
#include "ActionState.h"
#include "Animation.h"

class Composite;


class PlayerRunState : public ActionState
{
public:
	PlayerRunState();

	virtual void init();

	void enter();

	void run(InputHandle* input);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void exit();

	mutable Animation anim;

	float groundAccel = 15.0f * 60;
	float maxVelX = 10.0f * 60;

	int framesAir = 0;
	int maxFramesAir = 7;

	GameTransform* transform;
	Composite* compIn;

};

