#pragma once
#include "Actor.h"
#include <memory>

//Player.h
/*
  The character that you control
*/

class ActionStateMap;
class GameTransform;
class PhysicsBody;
class PhysEventHandler;
class Animator;

class Player : public Actor
{
public:

	void start();

	std::string getTag() const { return "Player"; }

	PhysicsBody* body;
	ActionStateMap* states;
	GameTransform* transform;
	PhysEventHandler* collisioninfo;
	Animator* animator;

};

