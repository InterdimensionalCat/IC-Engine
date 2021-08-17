#pragma once

namespace ic {

	class Scene;
	class Tilemap;
	class Camera;
	class Parallax;

	class Level {
	public:
		Level(Scene* scene);

		void update();
		void draw(const float interpol);

		float getUpperBound() {
			return -1.0f;
		}

		float getLowerBound() {
			return mapheight + 1.0f;
		}

		float getLeftBound() {
			return 0.0f;
		}

		float getRightBound() {
			return mapwidth;
		}

		std::string getCurrentLevelName() const {
			return currentlevelname;
		}

		void loadLevel(const std::string& levelname);

		void reloadLevel() {
			Logger::info("Reloading level.");
			loadLevel(currentlevelname);
		}

		void changeLevel(const std::string newlevel = "") {
			if (newlevel == "") {
				Logger::info("Loading level newLevel_1.tmx.");
				loadLevel("newLevel_1-px");
			}
			else {
				Logger::info("Loading level {}.tmx.", newlevel);
				loadLevel(newlevel);
			}
		}

	private:

		friend class TilemapCollision;

		std::shared_ptr<Tilemap> tilemap;
		std::shared_ptr<Camera> camera;
		std::shared_ptr<Parallax> parallaxEngine;

		Scene* scene;
		std::string currentlevelname;

		float mapwidth;
		float mapheight;
	};
}