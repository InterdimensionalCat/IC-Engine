#pragma once
#include "ActionState.h"
#include "Animation.h"

class Composite;


class PlayerIdleState : public ActionState
{
public:
	PlayerIdleState();
	virtual void init();
	void enter();
	void exit();

	void run(InputHandle* input);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	mutable Animation anim;

	int framesAir = 0;
	int maxFramesAir = 7;

	GameTransform* transform;
	Composite* compIn;
};

