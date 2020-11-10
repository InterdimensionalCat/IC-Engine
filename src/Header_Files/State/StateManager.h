/*
  Class that manages the state of the game, current valid states are only the main menu state
  and the actual gameplay state, however if multiple gamestates are necessasary this is capable
  of handling that, and other states such as paused/option menu state will eventually use this
*/
#pragma once
#include <unordered_map>
#include <memory>

class Game;
class State;

class StateManager
{
public:
	StateManager(Game* in);

	//StateManager is one of the few objects in the engine 
	//that uses manual dynamic memory allocation
	~StateManager();

	void addState(State* state);
	void setState(const string &key);
	void tick(InputHandle* input);
	void draw(Renderer* renderer);

	Game* instance;
private:
	unordered_map<string, std::unique_ptr<State>> states;
	State* current = nullptr;
};

