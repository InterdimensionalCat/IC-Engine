#pragma once
#include <memory>

class Actor;
class InputHandle;
class Renderer;

class Behavior
{
public:

	virtual ~Behavior() {}
	virtual void start() = 0;
	virtual void tick(std::shared_ptr<InputHandle>& input) = 0;
	virtual void draw(std::shared_ptr<Renderer>& renderer) = 0;

	std::shared_ptr<Actor> getActor();
private:

	friend class Actor;

	std::shared_ptr<Actor> parent;
};

