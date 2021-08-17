#pragma once
#include "ActorID.h"

namespace ic {

	class ActorData;

	/**
	 * @brief class representing an actor slot
	 * @details class representing an actor slot, or more specifically
	 * an entry into the array of actors, new ActorEntries can be added
	 * over the lifespan of a game excecution, but ActorEntry spots cannot
	 * be removed unless a level load/reload occurs. Additionally, entries
	 * can be tagged as respawnable. This is the 'Entity' representation in ECS
	 * and is used to index into the component pools. This entry also keeps track of 
	 * which components are associated with this actor through a bitmask
	*/
	class ActorEntry
	{
	public:

		/**
		 * @brief Constructs an ActorEntry at a specific index in the actors array
		 * @details ActorEntries should only be constructed once, and should be created
		 * and recreated using the createNewEntry functions, by default loads the entry to
		 * an invalid actor entry
		 * @param index 
		*/
		ActorEntry(const size_t index);

		/*
		* @brief all data is cleared on destruction
		*/
		~ActorEntry() {
			id = ActorID();
			mask.clear();
			data.reset();
		}

		/**
		 * @brief emplaces new actor identification info within this actor entry,
		 * @details overrwrites any data that was previously in the entry
		 * @param typeName the actor type name to emplace
		 * @param variantName the variant name to emplace
		 * @param respawnable specifies whether or not this spot should be reserved
		 * for a potential actor respawn after this actor is despawned
		*/
		void createNewEntry(const std::string& typeName, const std::string& variantName,
			bool respawnable = false);

		/**
		 * @brief emplaces new actor identification info within this actor entry with map data
		 * @details overrwrites any data that was previously in the entry
		 * @param typeName the actor type name to emplace
		 * @param variantName the variant name to emplace
		 * @param obj pointer to map data associate with this actor
		 * @param respawnable specifies whether or not this spot should be reserved
		 * for a potential actor respawn after this actor is despawned
		*/
		void createNewEntry(const std::string& typeName, const std::string& variantName,
			const tmx::Object& obj, bool respawnable = false);

		/**
		 * @brief reset this actor entry back to an invalid actor state
		 * @details this avoids accidentally accessing data from an actor that
		 * has supposedly been despawned
		*/
		void resetEntry();

		/**
		 * @brief get the index of this ActorEntry
		 * @return the index
		*/
		size_t getIndex() const;


		/**
		 * @brief get the version of this ActorEntry
		 * @details get the version of this ActorEntry, which keeps track
		 * of how many times this Actor slot has been reused or respawned,
		 * currently unused
		 * @return the version of this ActorEntry
		*/
		unsigned long long getVersion() const;

		/**
		 * @brief get a read only reference underlying ActorID of this entry
		 * @return the ActorID
		*/
		const ActorID& getActorId() const;

		/**
		 * @brief check if this ActorEntry contains a valid actor
		 * @return true if this entry is valid
		*/
		bool isIdValid() const;

		/**
		 * @brief check if the actor at this entry has the specified component
		 * @param componentId the component id of the component to check
		 * @return true if the actor has the specified component
		*/
		bool hasComponent(const int componentId) const;

		/**
		 * @brief marks the specified component as added to this actor in the component bitmask
		 * @param componentId the component to mark as added
		*/
		void setComponent(const int componentId);

		/**
		 * @brief marks the specified component as removed from this actor in the component bitmask
		 * @param componentId the component to mark as removed
		*/
		void removeComponent(const int componentId);

		/**
		 * @brief retruns a read only pointer to the underlying ActorData for this actor
		 * @return the ActorData
		*/
		const std::shared_ptr<ActorData> getData() const {
			return data;
		}


		/**
		 * @brief checks if the current actor is respawnable
		 * @return true if this actor is respawnable
		*/
		const bool isRespawnable() const {
			return respawnable;
		}

		/**
		 * @brief check if this respawnable is currently active, or waiting to be respawned
		 * @return true if the actor is active
		*/
		const bool isActive() const {
			return active;
		}

		/**
		 * @brief set this respawnable actor as active or inactive
		 * @param isactive the active bool to set this actor to 
		*/
		void setActive(bool isactive) {
			active = isactive;
		}

	private:

		ActorID id;
		unsigned long long version;
		const size_t index;

		std::vector<bool> mask;
		std::shared_ptr<ActorData> data;
		bool respawnable = false;
		bool active = true;
	};
}

