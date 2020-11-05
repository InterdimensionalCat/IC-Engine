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
	StateManager(std::shared_ptr<Game> in);

	//StateManager is one of the few objects in the engine 
	//that uses manual dynamic memory allocation
	~StateManager();

	void addState(std::shared_ptr<State> state);
	void setState(const string &key);
	void tick(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	std::shared_ptr<Game> instance;
private:
	unordered_map<string, std::shared_ptr<State>> states;
	std::shared_ptr<State> current = nullptr;
};

