#include <memory>
#include "Scene.h"


namespace ic {

	class SceneManager {
	public:
		SceneManager() {
			currentScene = std::make_shared<Scene>();
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

		void update() {
			currentScene->update();
		}

		void draw(const float interpol) {
			currentScene->draw(interpol);
		}
	private:

		void changeSceneDelayed() {
			dirty = false;
		}

		std::string loadScene;
		bool dirty = false;

		inline static std::unique_ptr<SceneManager> instance;
		std::shared_ptr<Scene> currentScene;
	};
}