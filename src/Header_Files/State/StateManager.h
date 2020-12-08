/*
  Class that manages the state of the game, current valid states are only the main menu state
  and the actual gameplay state, however if multiple gamestates are necessasary this is capable
  of handling that, and other states such as paused/option menu state will eventually use this
*/
#pragma once
#include <unordered_map>
#include <memory>

class State;

class StateManager
{
public:
	StateManager();

	//StateManager is one of the few objects in the engine 
	//that uses manual dynamic memory allocation
	~StateManager();

	void addState(State* state);
	void setState(const std::string &key);
	void tick(InputHandle* input);
	void draw(Renderer* renderer);

private:
	std::unordered_map<std::string, std::unique_ptr<State>> states;
	State* current = nullptr;
};

