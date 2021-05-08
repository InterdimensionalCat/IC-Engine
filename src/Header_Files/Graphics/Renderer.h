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
#include "DrawableObjTree.h"
#include "ActorUID.h"

namespace ic::gfx {

	struct RenderEvent;
	class DrawableObject;
	class RenderComponent;

	class Renderer
	{
	public:

		Renderer();
		~Renderer();

		void preRender(const float interpol);
		void render();
		void postRender();
		void updateInput();
		void addEvent(std::unique_ptr<RenderEvent> event);

	private:


		friend struct RenderEvent;
		friend class DrawableObject;
		friend class DrawableVertices;


		friend struct LoadTextureEvent;
		friend struct UnloadTextureEvent;

		template <typename T>
		friend struct CreateDrawableObjectEvent;
		friend struct AddDrawableTreeChildBackEvent;
		friend struct AddDrawableTreeChildFrontEvent;
		friend struct RemoveDrawableTreeChildEvent;


		void loadTexture(const std::string& texturename);
		void unloadTexture(const std::string& texturename);
		Texture* getTexture(const std::string& texturename);

		void createDrawableTree(std::unique_ptr<DrawableObject> baseDrawable, const ActorUID& actor);
		void addDrawableTreeChildFront(const ActorUID parentID, const ActorUID childID);
		void addDrawableTreeChildBack(const ActorUID parentID, const ActorUID childID);
		void removeDrawableTreeChild(const ActorUID childID);


		sf::RenderWindow* getWindow();


		float interpol = 0.0f;
		sf::RenderStates states = sf::RenderStates::Default;
		std::unique_ptr<sf::RenderWindow> window;
		std::map<std::string, std::shared_ptr<Texture>> textures;


		//drawable trees data members

		//links actor IDS to the BASE drawable object in that actor's drawable
		std::map<ic::ActorUID, std::shared_ptr<DrawableObjTree>> actorToTreeMap;

		//renderer draws all trees sequentially from this vector on render();
		std::vector<std::shared_ptr<DrawableObjTree>> drawableTrees;

		void handleEvents();
		bool pollEvent(std::unique_ptr<RenderEvent>& event);
		std::queue<std::unique_ptr<RenderEvent>> renderEventQueue;

		void addDrawableTreeChild(const ic::ActorUID parentID, const ic::ActorUID childID, bool front);
	};
}

