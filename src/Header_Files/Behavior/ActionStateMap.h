#pragma once
#include <unordered_map>
#include "Behavior.h"

class ActionState;

class ActionStateMap : public Behavior
{
public:

	void addState(ActionState* state);

	void setState(const string &key, InputHandle* input);
	void setState(const string &key);

	void tick(InputHandle* input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void start();

private:
	unordered_map<string, shared_ptr<ActionState>> map;
	ActionState* current = nullptr;
};

