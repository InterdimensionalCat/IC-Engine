#include "include.h"
#include "GameState.h"
#include "Level.h"



GameState::GameState(StateManager* p) : State(p) {

}

GameState::~GameState() {
	for (auto it = levels.begin(); it != levels.end(); it++) {
		Level* dummy = nullptr;
		std::swap(dummy, it->second);
		delete dummy;
	}

	levels.clear();
}

void GameState::init() {
	currentLevel = new Level();
	levels.emplace("level1", currentLevel);
}

void GameState::enter() {
	currentLevel->loadFrom("");

}

void GameState::tick(InputHandle* input) {
	currentLevel->tick(input);
}
void GameState::draw(Renderer* renderer) {
	currentLevel->draw(renderer);
}
void GameState::exit() {

}