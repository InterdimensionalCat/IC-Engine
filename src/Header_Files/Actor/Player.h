#pragma once
#include "Actor.h"

class ActionStateMap;
class GameTransform;
class PhysicsBody;
class PhysEventHandler;
class Animator;

class Player : public Actor
{
public:

	void start();

	string getTag() const { return "Player"; }

	PhysicsBody* body;
	ActionStateMap* states;
	GameTransform* transform;
	PhysEventHandler* collisioninfo;
	Animator* animator;

};

