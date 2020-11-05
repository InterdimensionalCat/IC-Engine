#pragma once
#include "Behavior.h"
#include <vector>
#include <memory>

class PhysicsEngine;
class CollisionEvent;

class PhysEventHandler : public Behavior {
public:
	virtual void start();
	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);

	std::shared_ptr<PhysicsEngine> engine;
	std::vector<CollisionEvent> events;
};