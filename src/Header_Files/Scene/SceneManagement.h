#include <memory>
#include "Scene.h"
#include "MainMenu.h"

namespace ic {

	class SceneManager {
	public:
		SceneManager() {
			//currentScene = std::make_shared<MainMenu>();
			addScene(std::make_shared<MainMenu>());
			addScene(std::make_shared<GameScene>());
			currentScene = scenes.find("MainMenuState")->second;
			loadScene = "MainMenuState";
		}

		void addScene(std::shared_ptr<Scene> scene) {
			scenes.emplace(scene->getName(), scene);
		}

		static void create() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<SceneManager>();
			}
		}

		static SceneManager* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<SceneManager>();
			}
			return instance.get();
		}

		void changeScene(std::string sceneName) {
			loadScene = sceneName;
			dirty = true;
		}

		static void changeSceneStatic(std::string sceneName) {
			instance.get()->changeScene(sceneName);
		}

		void update() {
			currentScene->update();
			if (dirty) {
				changeSceneDelayed();
			}
		}

		void draw(const float interpol) {
			currentScene->draw(interpol);
		}
	private:

		void changeSceneDelayed() {
			dirty = false;
			Logger::debug("Loading Scene {} ", loadScene);
			auto it = scenes.find(loadScene);
			if (it == scenes.end()) {
				Logger::error("Scene {} not found!", loadScene);
				throw std::exception();
			}

			currentScene = it->second;
		}

		std::string loadScene;
		bool dirty = false;

		inline static std::unique_ptr<SceneManager> instance;
		std::shared_ptr<Scene> currentScene;
		std::map<std::string, std::shared_ptr<Scene>> scenes;
	};
}