#pragma once

class StateManager;
class InputHandle;
class PhysicsEngine;
class Renderer;

enum class TimeStepType {Fixed, Variable};

struct WindowData {
	WindowData(RenderWindow* wind);
	unique_ptr <RenderWindow> window;
	RenderStates states;
	RenderWindow* get() {
		return window.get();
	}
};

class Game {
public:

	Game();

	void tick(const float dt);
	void draw(const float interpol);
	void game();
	void stop();


	//Game Loop Objects
	unique_ptr<Clock> timer;
	unique_ptr <InputHandle> input;
	unique_ptr <StateManager> manager;
	unique_ptr <Renderer> renderer;


	//settings
	const string TITLE = "Game Engine 2020";
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	float targetFPS = 60.0f;
	const float targetDT = 1.0f / 60.0f;
	float dt;

	bool debug = false;
	bool paused = false;
	bool vsync = false;
	bool running = true;
	TimeStepType timeType = TimeStepType::Fixed;

	float currentfps = 0;
	Clock fpstimer;

	//windows
	WindowData* MainWindow;
	map<string, unique_ptr<WindowData>> subwindows;
};

extern Game* instance;

