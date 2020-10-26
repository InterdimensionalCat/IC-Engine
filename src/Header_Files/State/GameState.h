#pragma once
#include <unordered_map>
#include "State.h"

class Level;

class GameState :
	public State
{
public:
	GameState(StateManager* p);
	virtual ~GameState();
	virtual void init();
	virtual void enter();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	virtual void exit();
	virtual string getName() const { return "GAME"; }

	string getCurrentLevel() {
		return "";
	}

	void switchLevel(const string &next) {

	}

	unordered_map<string, Level*> levels;
	Level* currentLevel;
};

