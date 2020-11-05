#pragma once
#include "Behavior.h"
#include <string>
#include <memory>

class ActionStateMap;

class ActionState
{
public:
	virtual ~ActionState() {}
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void run(std::shared_ptr<InputHandle>& input) = 0;
	virtual void exit() = 0;
	string getName() { return name; };
	virtual void draw(std::shared_ptr<Renderer>& renderer) = 0;

	std::shared_ptr<ActionStateMap> parent = std::shared_ptr<ActionStateMap>(nullptr);
	std::string name = "no name";
};

