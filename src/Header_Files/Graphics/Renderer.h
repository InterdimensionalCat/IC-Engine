#pragma once
#include <vector>

class Game;
struct WindowData;

class Renderer
{
public:

	Renderer(Game* in);
	~Renderer();

	WindowData* getWindowData();
	WindowData* getWindowData(const std::string &subwindowname);

	float interpol;
	Game* instance;
};

