#pragma once
#include "Behavior.h"
#include <string>

class ActionStateMap;

class ActionState
{
public:
	virtual ~ActionState() {}
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void run(InputHandle* input) = 0;
	virtual void exit() = 0;
	string getName() { return name; };
	virtual void draw(Renderer* renderer) = 0;

	ActionStateMap* parent;
	std::string name;
};

