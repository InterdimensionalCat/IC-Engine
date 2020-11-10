#include "include.h"
#include "GameState.h"
#include "Level.h"



GameState::GameState(StateManager* p) : State(p), currentLevel(nullptr) {

}

GameState::~GameState() {

}

void GameState::init() {
	levels.emplace("level1", std::make_unique<Level>());
	currentLevel = levels.at("level1").get();
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