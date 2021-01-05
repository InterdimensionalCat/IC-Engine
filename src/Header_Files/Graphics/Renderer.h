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
#include <map>
#include <memory>
#include <queue>
#include "SFML\Graphics.hpp"
#include "Texture.h"
#include "DrawableObject.h"

namespace ic {

	struct RenderEvent;
	class DrawableObject;
	class RenderComponent;

	class Renderer
	{
	public:

		Renderer();
		~Renderer();
		void updateInput();
		void preRender(const float interpol);
		void render();
		void postRender();
		void addEvent(std::unique_ptr<RenderEvent> event);

		void loadTexture(const std::string &texturename);
		void unloadTexture(const std::string& texturename);
		void addDrawable(std::unique_ptr<DrawableObject> drawableToAdd);
		void makeChild(const ActorUID& parentUID, const ActorUID& childUID);
		void makeIndependent(const ActorUID& childUID);
		void updateDrawableComponents();
	private:

		friend class DrawableObject;

		float interpol = 0.0f;
		sf::RenderStates states = sf::RenderStates::Default;
		std::unique_ptr<sf::RenderWindow> window;
		std::map<std::string, std::unique_ptr<ic::Texture>> textures;
		std::vector<std::unique_ptr<DrawableObject>> drawables;

		std::vector<std::unique_ptr<RenderComponent>> components;

		void handleEvents();
		bool pollEvent(std::unique_ptr<RenderEvent>& event);
		std::queue<std::unique_ptr<RenderEvent>> renderEventQueue;
	};
}

