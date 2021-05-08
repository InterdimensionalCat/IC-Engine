#pragma once
#include "Behavior.h"
#include <string>
#include <memory>
//ActionState.h
/*
  A single abstract state in the ActionStateMap.
*/
class ActionStateMap;

class ActionState
{
public:
	virtual ~ActionState() {}
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void run(InputHandle* input) = 0;
	virtual void exit() = 0;
	std::string getName() { return name; };
	virtual void draw(Renderer* renderer) = 0;

	ActionStateMap* parent = nullptr;
	std::string name = "no name";
};

