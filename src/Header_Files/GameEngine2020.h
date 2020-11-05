#pragma once

class StateManager;
class InputHandle;
class PhysicsEngine;
class Renderer;

enum class TimeStepType {Fixed, Variable};

class Game {
public:

	Game();

	void tick(const float dt);
	void draw(const float interpol);
	void game();
	void stop();


	//Game Loop Objects
	shared_ptr <sf::Clock> timer;
	shared_ptr <InputHandle> input;
	shared_ptr <StateManager> manager;
	shared_ptr <Renderer> renderer;


	//settings
	const string TITLE = "Game Engine 2020";
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	float targetFPS = 60.0f;
	const float targetDT = 1.0f / 60.0f;
	float dt = 0.0f;

	bool debug = false;
	bool paused = false;
	bool vsync = false;
	bool running = true;
	TimeStepType timeType = TimeStepType::Fixed;

	float currentfps = 0;
	sf::Clock fpstimer = sf::Clock();

	//windows
};

extern std::shared_ptr<Game> instance;

