#pragma once
#include "Behavior.h"

class ActionStateMap;

class ActionState :
	public Drawable
{
public:
	virtual ~ActionState() {}
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void run(InputHandle* input) = 0;
	virtual void exit() = 0;
	string getName() { return name; };
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	ActionStateMap* parent;
	string name;
};

