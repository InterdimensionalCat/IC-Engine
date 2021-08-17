#pragma once

namespace ic {

	enum class SystemType;
	class System;
	class Scene;

	class SystemManager {
	public:
		SystemManager(Scene* scene);
		void runSystemsInRange(const SystemType begin, const SystemType end);
	private:

		Scene* scene;

		std::vector<std::shared_ptr<System>> systems;
	};
}