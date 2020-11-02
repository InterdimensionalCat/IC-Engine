#pragma once
#include "ActionState.h"

class PlayerMoveState : public ActionState
{
public:
	PlayerMoveState();
	virtual ~PlayerMoveState() {}

	void init();

	void enter();

	void run(InputHandle* input);
	void draw(Renderer* renderer);

	void exit();

	float groundAccel = 15.0f * 60;
	float maxVelX = 10.0f * 60;

	int framesAir = 0;
	int maxFramesAir = 7;
};

