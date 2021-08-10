#pragma once

#include "Scene.h"
#include "ActorEntry.h"
#include "ComponentPool.h"
#include "ActorPool.h"

namespace ic {

	class Animatable;
	//recovery

	class ComponentManager {
	public:
		ComponentManager(Scene* scene) : scene(scene) {}
		~ComponentManager() {
			componentPools.clear();
		}

		template<typename T, typename... Args>
		T* assignComponent(std::shared_ptr<ActorEntry> entry, Args&&... args) {
			auto idind = entry->getIndex();
			int componentId = getComponentId<T>();
			if (componentPools.size() <= componentId) {
				componentPools.resize(componentId + 1, std::shared_ptr<TypedComponentPool<T>>(nullptr));
			}

			if (componentPools.at(componentId).get() == nullptr) {
				componentPools.at(componentId) 
					= std::make_shared<TypedComponentPool<T>>(scene->actorPool->maxActors);
			}

			auto poolTyped = static_cast<TypedComponentPool<T>*>(componentPools.at(componentId).get());


			poolTyped->setIndex(idind, args...);
			T* component = static_cast<T*>(poolTyped->at(idind));
			entry->setComponent(componentId);
			return component;
		}

		template<typename T>
		T* getComponent(const std::shared_ptr<ActorEntry> entry) {
			int componentId = getComponentId<T>();
			if (!entry->hasComponent(componentId)) {
				return nullptr;
			}

			T* component = static_cast<T*>(componentPools.at(componentId)->at(entry->getIndex()));
			return component;
		}

		template<typename T>
		const T* getComponent(const std::shared_ptr<ActorEntry> entry) const {
			int componentId = getComponentId<T>();
			if (!entry->hasComponent(componentId)) {
				return nullptr;
			}

			T* component = static_cast<T*>(componentPools.at(componentId).at(entry->getIndex()));
			return component;
		}

		template<typename T>
		void removeComponent(std::shared_ptr<ActorEntry> entry) {
			if (entry->isIdValid()) {
				int componentId = getComponentId<T>();
				entry->removeComponent(componentId);
				componentPools.at(componentId)->removeComponent(entry->getIndex());
			}
		}

	private:

		friend class Level;
		friend class ActorPool;

		Scene* scene;

		std::vector<std::shared_ptr<ComponentPool>> componentPools;
	};

	extern int componentCounter;
	template <class T>
	int getComponentId() {
		static int componentId = componentCounter++;
		return componentId;
	}
}
