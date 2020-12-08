#pragma once
#include <memory>

//State.h
/*
  abstract class that populates the StateManager object
*/

class StateManager;
class InputHandle;

class State
{
public:
	State(StateManager* p);
	virtual ~State();
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void tick(InputHandle* input) = 0;
	virtual void draw(Renderer* renderer) = 0;
	virtual void exit() = 0;
	virtual std::string getName() const = 0;

	StateManager* parent;
};

