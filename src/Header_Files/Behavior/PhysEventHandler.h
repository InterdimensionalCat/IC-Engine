#pragma once
#include "Behavior.h"
#include <vector>
#include <memory>
//PhysEventHandler
/*
  Behavior that picks up collision events so that other behaviors
  can get information about collisions this object was involved in
*/

class PhysicsEngine;
class CollisionEvent;

class PhysEventHandler : public Behavior {
public:
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);

	PhysicsEngine* engine;
	std::vector<CollisionEvent> events;
};