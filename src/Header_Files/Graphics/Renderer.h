//Renderer.h
/*
  The renderer class is mostly just a container class,
  its purpose is to hold all the variables that the draw call requires
  for now that is just what SFML's draw needs (a RenderTarget and RenderStates)
  and an interpolation value

  states gets set to RenderStates::Default and interpol gets updated at the beginning
  of each draw call
*/
#pragma once
#include <vector>

class Game;
struct WindowData;

class Renderer
{
public:

	Renderer();
	~Renderer();

	float interpol = 0.0f;
	std::unique_ptr<sf::RenderWindow> window;
	sf::RenderStates states = sf::RenderStates::Default;
};

