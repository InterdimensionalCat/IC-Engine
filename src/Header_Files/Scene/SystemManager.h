#pragma once

namespace ic {

	enum class SystemType;
	class System;
	class GameScene;

	class SystemManager {
	public:
		SystemManager(GameScene* scene);
		void runSystemsInRange(const SystemType begin, const SystemType end);
	private:

		GameScene* scene;

		std::vector<std::shared_ptr<System>> systems;
	};
}