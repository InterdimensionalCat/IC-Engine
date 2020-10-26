#pragma once
#include "ActionState.h"
#include "Animation.h"

class Composite;


class PlayerJumpState : public ActionState
{
public:
	PlayerJumpState();

	virtual void init();

	void enter();

	void run(InputHandle* input);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void exit();

	mutable Animation anim;

	float velXatJump;

	float jump = 1000.0f * 60;
	float airaccel = 10.0f * 60;
	float maxVelX = 13.0f * 60;
	Vector2f jumpangle;

	GameTransform* transform;
	Composite* compIn;
};