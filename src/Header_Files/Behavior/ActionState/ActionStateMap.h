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

	void addState(std::shared_ptr<ActionState>& state);

	void setState(const string &key, std::shared_ptr<InputHandle>& input);
	void setState(const string &key);

	void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);
	void start();

	std::shared_ptr<PhysicsBody> body;
	std::shared_ptr<GameTransform> transform;
	std::shared_ptr<PhysEventHandler> collisioninfo;
	std::shared_ptr<Animator> animator;

private:
	std::unordered_map<std::string, shared_ptr<ActionState>> map;
	std::shared_ptr<ActionState> current = std::shared_ptr<ActionState>(nullptr);
};

