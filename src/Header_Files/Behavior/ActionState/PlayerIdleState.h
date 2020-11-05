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

	void run(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	int framesAir = 0;
	int maxFramesAir = 7;
};

