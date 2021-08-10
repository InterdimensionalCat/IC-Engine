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


	class Scene {
	public:

		Scene();
		~Scene();

		void update();
		void draw(const float interpol);

		std::shared_ptr<AudioEngine> audio;

		std::shared_ptr<Window> window;
		std::shared_ptr<KeyboardHandle> input;

		std::shared_ptr<ComponentManager> compManager;
		std::shared_ptr<Level> levels;
		std::shared_ptr<SceneEventManager> sceneEvents;
		std::shared_ptr<SystemManager> sysManager;
		std::shared_ptr<ActorPool> actorPool;


		std::vector<sf::RectangleShape> debugShapes;


	};
}
