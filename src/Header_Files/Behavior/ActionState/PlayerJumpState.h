#pragma once
#include "ActionState.h"

class PlayerJumpState : public ActionState
{
public:
	PlayerJumpState();
	virtual ~PlayerJumpState() {}

	void init();

	void enter();

	void run(InputHandle* input);
	void draw(Renderer* renderer);

	void exit();

	float velXatJump = 0.0f;

	float jump = 100.0f * 60 * 60 * 60;
	float airaccel = 2.5f * 60 * 60 * 60;
	float maxVelX = 5.0f * 60 * 60 * 60;
	s2d::NormalVec jumpangle = s2d::NormalVec(0,-1);

};