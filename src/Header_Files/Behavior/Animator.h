#pragma once
#include <unordered_map>
#include "Behavior.h"

class Animation;
class GameTransform;

class Animator : public Behavior {
public:
	void addAnimation(Animation* anim);
	void setAnimation(const std::string& key);

	void tick(InputHandle* input);
	void draw(Renderer* renderer);
	void start();

	GameTransform* transform;
	Animation* current = nullptr;

private:
	std::unordered_map<std::string, shared_ptr<Animation>> map;
};