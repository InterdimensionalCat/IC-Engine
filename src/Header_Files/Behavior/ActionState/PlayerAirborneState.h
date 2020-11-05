#pragma once
#include "ActionState.h"

class PlayerAirborneState : public ActionState
{
public:
	PlayerAirborneState();
	virtual ~PlayerAirborneState() {}

	virtual void init();

	void enter();

	void run(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	void exit();

	float airaccel = 2.5f * 60 * 60;
	float maxVelX = 5.0f * 60 * 60;

};