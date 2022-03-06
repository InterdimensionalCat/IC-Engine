#include "include.h"
#include "BoopAI.h"

using namespace ic;


BoopAI::BoopAI(const std::shared_ptr<Port> port) 
	: GameInputDevice(port) {}

void BoopAI::update() {
	keylistener.update();
}

bool BoopAI::isDown(const GameInputButton key) const {
	return keylistener.isDown(key);
}

bool BoopAI::isPressed(const GameInputButton key) const {
	return keylistener.isPressed(key);
}

void BoopAI::pressKey(const GameInputButton key) {
	keylistener.pressKey(key);
}

void BoopAI::releaseKey(const GameInputButton key) {
	keylistener.releaseKey(key);
}