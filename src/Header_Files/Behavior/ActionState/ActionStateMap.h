#pragma once
#include <unordered_map>
#include "Behavior.h"

//ActionStateMap.h
/*
  A very powerful structure that can create both complex behavior responding to player input, as well as
  create complex AI for enemies. It is a Finite State Machine that runs logic from the current state, and
  can switch to other states according to input or other factors
*/

class ActionState;
class Animator;
class GameTransform;
class PhysicsBody;
class PhysEventHandler;

class ActionStateMap : public Behavior
{
public:

	void addState(ActionState* state);

	void setState(const string &key, InputHandle* input);
	void setState(const string &key);

	void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	void start();

	PhysicsBody* body;
	GameTransform* transform;
	PhysEventHandler* collisioninfo;
	Animator* animator;
	std::unordered_map<std::string, float> speedValues;

private:
	std::unordered_map<std::string, unique_ptr<ActionState>> map;
	ActionState* current = nullptr;
};

