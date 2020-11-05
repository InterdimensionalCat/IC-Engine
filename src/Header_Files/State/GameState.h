//GameState.h
/*
  State that controls the "main game state" whatever that might be.
  For this game the main job of the gamestate will mostly be level management/transition
*/
#pragma once
#include <unordered_map>
#include "State.h"

class Level;

class GameState :
	public State
{
public:
	GameState(std::shared_ptr<StateManager> p);
	virtual ~GameState();
	virtual void init();
	virtual void enter();
	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);
	virtual void exit();
	virtual string getName() const { return "GAME"; }

	string getCurrentLevel() {
		return "";
	}

	void switchLevel(const string &next) {

	}

	unordered_map<string, std::shared_ptr<Level>> levels;
	Level* currentLevel;
};

