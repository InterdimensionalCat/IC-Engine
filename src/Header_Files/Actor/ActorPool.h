#pragma once

namespace ic {
	
	class ActorEntry;
	class Scene;

	class ActorPool {
	public:
		ActorPool(Scene* scene);
		~ActorPool();

		void despawnActor(std::shared_ptr<ActorEntry> entry);

		void respawnActor(std::shared_ptr<ActorEntry> entry);

		std::shared_ptr<ActorEntry> spawnActor(const std::string& typeName, 
			const std::string& variantName);

		std::shared_ptr<ActorEntry> spawnActor(const std::string& typeName, 
			const std::string& variantName, const tmx::Object& obj);
		
		std::shared_ptr<json> createJsonFromActor(std::shared_ptr<ActorEntry> entry);

		void saveActorJsonToFile(std::shared_ptr<json> data, 
			const std::string& filename);

		std::vector<std::shared_ptr<ActorEntry>> actors;

	private:

		friend class Level;
		friend class ComponentManager;

		Scene* scene;

		size_t maxActors = 1;
		std::vector<std::shared_ptr<ActorEntry>> freeActors;
	};
}