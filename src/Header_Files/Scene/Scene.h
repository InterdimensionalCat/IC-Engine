#pragma once

//#include "Window.h"
//#include "MapParser.h"
//#include "ComponentPool.h"
//#include "Parallax.h"
//#include "Camera.h"
//#include "Tilemap.h"
//#include "Input.h"
//#include "PhysicsEngine.h"
//#include "AudioEngine.h"
//#include "ActorEntry.h"
//#include "SceneEvent.h"



namespace ic {

	class ComponentManager;
	class Level;
	class SystemManager;
	class ActorPool;
	class SceneEventManager;

	class Window;
	class Camera;
	class parallax;
	class Tilemap;
	class AudioEngine;
	class Parallax;
	class KeyboardHandle;


	/**
	 * @brief The main class that manages the rest of the engine
	 * @details The main class that manages the rest of the engine, stores and manages
	 * the Entities, Components, and Systems in the ECS implimentation, and drives both the
	 * audio and is the primary rendering class
	 * @todo create an actor debug system where actors can be added to the debug list
	 * which has methods that only function when debug mode is enabled, such as drawing
	 * debug hitboxes
	*/
	class Scene {
	public:

		/**
		 * @brief constructs all the managers and objects of the scene and loads the first level
		*/
		Scene();

		/*
		* @brief clears active registries on destruction
		*/
		~Scene();

		/**
		 * @brief updates input and all actors based on the currently registered systems
		 * @brief additionally calls the update function for the current level
		*/
		void update();

		/**
		 * @brief calls graphics related systems currently registered
		 * @details additionally calls the draw function for the current level
		 * @param interpol the calculated per frame interpolation value
		*/
		void draw(const float interpol);

		/**
		 * @brief stores and controls the component portion of ECS
		 * @details contains functions for creating and assigning components
		 * to actors
		*/
		std::shared_ptr<ComponentManager> compManager;

		/**
		 * @brief stores, loads, updates, and controls various elements of the map
		 * @details including the parallax background and tilemap
		*/
		std::shared_ptr<Level> levels;

		/**
		 * @brief recieves and calls scenewide events
		 * @details such as actor creation, deletion, or respawning, or 
		 * events that affect the active level
		*/
		std::shared_ptr<SceneEventManager> sceneEvents;

		/**
		 * @brief stores and controls the system portion of ECS
		*/
		std::shared_ptr<SystemManager> sysManager;

		/**
		 * @brief stores the actor(or entity) portion of ECS
		 * @details allows manipulation of actors
		*/
		std::shared_ptr<ActorPool> actorPool;


		//std::vector<sf::RectangleShape> debugShapes;


	};
}
