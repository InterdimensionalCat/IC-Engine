#pragma once
#include <memory>

class StateManager;
class InputHandle;

class State
{
public:
	State(std::shared_ptr<StateManager> p);
	virtual ~State();
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void tick(std::shared_ptr<InputHandle>& input) = 0;
	virtual void draw(std::shared_ptr<Renderer>& renderer) = 0;
	virtual void exit() = 0;
	virtual string getName() const = 0;

	std::shared_ptr<StateManager> parent;
};

