#include "include.h"
#include "Animator.h"
#include "Animation.h"
#include "GameTransform.h"
#include "Actor.h"

void Animator::addAnimation(Animation* anim) {
	anim->parent = this;
	map.emplace(anim->getName(), shared_ptr<Animation>(anim));
	if (current == nullptr) {
		current = map.at(anim->getName()).get();
		current->reset();
	}
}

void Animator::setAnimation(const std::string& key) {
	if (map.find(key) != map.end()) {
		current = map.at(key).get();
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

void Animator::tick(InputHandle* input) {

}

void Animator::draw(Renderer* renderer) {
	current->draw(renderer);
}