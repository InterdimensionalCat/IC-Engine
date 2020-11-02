#pragma once
#include <unordered_map>
#include "Behavior.h"

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

	Animator* animator;
	GameTransform* transform;
	PhysicsBody* body;
	PhysEventHandler* collisioninfo;

private:
	std::unordered_map<std::string, shared_ptr<ActionState>> map;
	ActionState* current = nullptr;
};

