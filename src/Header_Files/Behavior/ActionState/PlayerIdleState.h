#pragma once
#include "ActionState.h"

class PlayerIdleState : public ActionState
{
public:
	PlayerIdleState();
	virtual ~PlayerIdleState() {}

	void init();
	void enter();
	void exit();

	void run(InputHandle* input);
	void draw(Renderer* renderer);

	int framesAir = 0;
	int maxFramesAir = 7;
};

