#pragma once
#include "ActionState.h"

class PlayerMoveState : public ActionState
{
public:
	PlayerMoveState();
	virtual ~PlayerMoveState() {}

	void init();

	void enter();

	void run(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	void exit();

	float groundAccel = 15.0f * 60 * 60;
	float maxVelX = 10.0f * 60 * 60;

	int framesAir = 0;
	int maxFramesAir = 7;
};

