#pragma once
#include "ActionState.h"

class PlayerAirborneState : public ActionState
{
public:
	PlayerAirborneState();
	virtual ~PlayerAirborneState() {}

	virtual void init();

	void enter();

	void run(InputHandle* input);
	void draw(Renderer* renderer);

	void exit();

	float airaccel = 2.5f * 60;
	float maxVelX = 5.0f * 60;

};