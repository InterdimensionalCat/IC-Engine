#pragma once
#include "Actor.h"

class Composite;
class ActionStateMap;
class GameTransform;

class Player : public Actor
{
public:

	void start();
	void tick(InputHandle* input);

	string getTag() const { return "Player"; }

	Composite* comp;
	ActionStateMap* states;
	GameTransform* transform;

};

