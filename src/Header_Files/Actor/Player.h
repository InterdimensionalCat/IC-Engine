#pragma once
#include "Actor.h"
#include <memory>

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

	std::shared_ptr<PhysicsBody> body;
	std::shared_ptr<ActionStateMap> states;
	std::shared_ptr<GameTransform> transform;
	std::shared_ptr<PhysEventHandler> collisioninfo;
	std::shared_ptr<Animator> animator;

};

