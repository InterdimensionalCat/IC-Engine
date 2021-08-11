#pragma once

namespace ic {
	
	class ActorEntry;
	class Scene;

	/**
	 * @brief manager class for scene actors
	 * @details allows for spawning, despawning,
	 * and respawning actors, as well as converting actor data
	 * to json files and saving them. Most of these should not be called
	 * directly and should instead be used indirectly through the
	 * corrosponding scene event, as spawning/despawning actors in
	 * the middle of an update cycle can cause problems
	*/
	class ActorPool {
	public:

		/**
		 * @brief constructs an actor pool for the given scene
		 * @param scene the scene to construct with
		*/
		ActorPool(Scene* scene);

		/*
		* @brief the actor vectors are cleared on destruction
		*/
		~ActorPool();

		/**
		 * @brief spawns a new actor with no map data
		 * @param typeName the actor type name to spawn
		 * @param variantName the actor variant name to spawn
		 * @return a pointer to the created actor entry
		*/
		std::shared_ptr<ActorEntry> spawnActor(const std::string& typeName,
			const std::string& variantName);

		/**
		 * @brief spawns a new actor with map data
		 * @param typeName the actor type name to spawn
		 * @param variantName the actor variant name to spawn
		 * @param obj pointer to map data for this actor
		 * @return a pointer to the created actor entry
		*/
		std::shared_ptr<ActorEntry> spawnActor(const std::string& typeName,
			const std::string& variantName, const tmx::Object& obj);

		/**
		 * @brief despawns the supplied actor
		 * @param entry the actor entry of the actor to despawn
		*/
		void despawnActor(std::shared_ptr<ActorEntry> entry);

		/**
		 * @brief respawns the supplied respawnable actor
		 * @param entry the actor entry of the actor to respawn
		*/
		void respawnActor(std::shared_ptr<ActorEntry> entry);
		
		/**
		 * @brief creates a json from the current components attached to this actor
		 * @param entry the actor entry of the actor to create json data from
		 * @return a pointer to the created json data
		*/
		std::shared_ptr<json> createJsonFromActor(std::shared_ptr<ActorEntry> entry);

		/**
		 * @brief saves the supplied actor data json to a file
		 * @details saves to /resources/actors/[filename].json
		 * @param data the data to save to a file
		 * @param filename the file name to save the data to
		*/
		void saveActorJsonToFile(std::shared_ptr<json> data, 
			const std::string& filename);

		/**
		 * @brief gets the actor at the specified index
		 * @param index the index of the actor in the array
		 * @return a read and write pointer to the requested actor entry
		*/
		std::shared_ptr<ActorEntry> getActor(const size_t index) {
			return actors.at(index);
		}

		/**
		 * @brief get the size of the active actors vector
		 * @return the size of the active actors vector
		*/
		size_t size() const {
			return actors.size();
		}

	private:

		friend class Level;
		friend class ComponentManager;
		friend class Scene;

		Scene* scene;

		size_t maxActors = 1;
		std::vector<std::shared_ptr<ActorEntry>> freeActors;
		std::vector<std::shared_ptr<ActorEntry>> actors;
	};
}