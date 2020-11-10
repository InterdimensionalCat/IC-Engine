#pragma once
#include <unordered_map>
#include "Behavior.h"
#include <memory>

//Animator.h
/*
  The Animator is in charge of setting and drawing the proper animation on each frame,
  functions similarly to the ActionStateMap
*/

class Animation;
class GameTransform;

class Animator : public Behavior {
public:
	void addAnimation(Animation* anim);
	void setAnimation(const std::string& key);

	void tick(InputHandle* input);
	void draw(Renderer* renderer);
	void start();

	GameTransform* transform = nullptr;
	Animation* current = nullptr;

private:
	std::unordered_map<std::string, std::unique_ptr<Animation>> map;
};