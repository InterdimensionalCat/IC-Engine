#pragma once

class Actor;
class InputHandle;
class Renderer;

class Behavior
{
public:

	virtual ~Behavior() {}
	virtual void start() = 0;
	virtual void tick(InputHandle* input) = 0;
	virtual void draw(Renderer* renderer) = 0;

	Actor* getActor();
private:

	friend class Actor;

	Actor* parent;
};

