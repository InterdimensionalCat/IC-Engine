#pragma once
#include <unordered_map>

class Game;
class State;

class StateManager
{
public:
	StateManager(Game* in);
	~StateManager();

	void addState(State* state);
	void setState(const string &key);
	void tick(InputHandle* input);
	void draw(Renderer* renderer);

	Game* instance;
private:
	unordered_map<string, State*> states;
	State* current = nullptr;
};

