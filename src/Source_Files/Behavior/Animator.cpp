#include "include.h"
#include "Animator.h"
#include "Animation.h"
#include "GameTransform.h"
#include "Actor.h"

void Animator::addAnimation(std::shared_ptr<Animation>& anim) {
	anim->parent = std::shared_ptr<Animator>(this);
	map.emplace(anim->getName(), shared_ptr<Animation>(anim));
	if (current.get() == nullptr) {
		current = map.at(anim->getName());
		current->reset();
	}
}

void Animator::setAnimation(const std::string& key) {
	if (map.find(key) != map.end()) {
		current = map.at(key);
		current->reset();
	}
	else {
#ifdef _DEBUG
		cerr << "Action State " << key << " does not exist!\n";
		throw exception();
#endif
	}
}

void Animator::start() {
	transform = getActor()->getBehavior<GameTransform>();
}

void Animator::tick(std::shared_ptr<InputHandle>& input) {

}

void Animator::draw(std::shared_ptr<Renderer>& renderer) {
	current->draw(renderer);
}