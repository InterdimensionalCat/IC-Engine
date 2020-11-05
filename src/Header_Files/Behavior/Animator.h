#pragma once
#include <unordered_map>
#include "Behavior.h"
#include <memory>

class Animation;
class GameTransform;

class Animator : public Behavior {
public:
	void addAnimation(std::shared_ptr<Animation>& anim);
	void setAnimation(const std::string& key);

	void tick(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);
	void start();

	std::shared_ptr<GameTransform> transform = std::shared_ptr<GameTransform>(nullptr);
	std::shared_ptr<Animation> current = std::shared_ptr<Animation>(nullptr);

private:
	std::unordered_map<std::string, shared_ptr<Animation>> map;
};