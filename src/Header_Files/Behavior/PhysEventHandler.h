#pragma once
#include "Behavior.h"
#include <vector>

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