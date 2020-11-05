#include "include.h"
#include "GameState.h"
#include "Level.h"



GameState::GameState(std::shared_ptr<StateManager> p) : State(p), currentLevel(nullptr) {

}

GameState::~GameState() {

}

void GameState::init() {
	auto level1 = std::make_shared<Level>();
	levels.emplace("level1", level1);
	currentLevel = level1.get();
}

void GameState::enter() {
	currentLevel->loadFrom("");
}

void GameState::tick(std::shared_ptr<InputHandle>& input) {
	currentLevel->tick(input);
}
void GameState::draw(std::shared_ptr<Renderer>& renderer) {
	currentLevel->draw(renderer);
}
void GameState::exit() {

}