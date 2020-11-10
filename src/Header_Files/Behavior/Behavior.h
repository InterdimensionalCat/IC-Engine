#pragma once
#include <memory>

class Actor;
class InputHandle;
class Renderer;
//Behavior.h
/*
  Base class for all behaviors; behaviors are scripts atachable to actors, which,
  allows multiple objects to share some trait/behavior without code duplication
*/
class Behavior
{
public:

	virtual ~Behavior() {}
	virtual void start() = 0;
	virtual void tick(InputHandle* input) = 0;
	virtual void draw(Renderer* renderer) = 0;

	//allows behaviors to access the actor they are attached to;
	//which is necessasry for behaviors to query for other behaviors
	//attached to the object
	Actor* getActor();
private:

	friend class Actor;

	Actor* parent;
};

