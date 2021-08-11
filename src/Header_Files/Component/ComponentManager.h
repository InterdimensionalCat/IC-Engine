#pragma once

#include "Scene.h"
#include "ActorEntry.h"
#include "ComponentPool.h"
#include "ActorPool.h"

namespace ic {

	/**
	 * @brief manager class for the actor components in the scene
	*/
	class ComponentManager {
	public:

		/**
		 * @brief constructs a ComponentManager for the given scene
		 * @param scene the scene to construct a ComponentManager for
		*/
		ComponentManager(Scene* scene) : scene(scene) {}
		~ComponentManager() {
			componentPools.clear();
		}

		/**
		 * @brief assign a component to the supplied actor
		 * @details constructs the component in-place in the pool with the 
		 * supplied arguments
		 * @tparam T the type of the component to assign
		 * @tparam ...Args variatic param for constructing the component with args
		 * @param entry the actor entry to add a component to
		 * @param ...args the arguments to construct the component from; optional
		 * @return a raw pointer to the created component, since the component pool manages
		 * the component memory a smart pointer is not appropreate here
		*/
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

		/**
		 * @brief gets a pointer to the requested component for the supplied actor if it exists
		 * @details returns nullptr if this actor does not have the requested component
		 * @tparam T the type of the requested component
		 * @param entry the actor entry to get the component from
		 * @return a raw pointer to the requested component if present, nullptr otherwise
		*/
		template<typename T>
		T* getComponent(const std::shared_ptr<ActorEntry> entry) {
			int componentId = getComponentId<T>();
			if (!entry->hasComponent(componentId)) {
				return nullptr;
			}

			T* component = static_cast<T*>(componentPools.at(componentId)->at(entry->getIndex()));
			return component;
		}

		/**
		 * @brief gets a read-only pointer to the requested component for the supplied actor if it exists
		 * @details returns nullptr if this actor does not have the requested component
		 * @tparam T the type of the requested component
		 * @param entry the actor entry to get the component from
		 * @return a raw pointer to the requested component if present, nullptr otherwise
		*/
		template<typename T>
		const T* getComponent(const std::shared_ptr<ActorEntry> entry) const {
			int componentId = getComponentId<T>();
			if (!entry->hasComponent(componentId)) {
				return nullptr;
			}

			T* component = static_cast<T*>(componentPools.at(componentId).at(entry->getIndex()));
			return component;
		}


		/**
		 * @brief retrives a component by modifying the pointer passed in to point to the component
		 * @details unlike the previous component functions, this one will throw if the component
		 * cannot be found
		 * @tparam T the type of the requested component
		 * @param entry the actor entry to get the component from
		 * @param comp a pointer that the component will be assigned to
		*/
		template<typename T>
		void getComponent(const std::shared_ptr<ActorEntry> entry, T*& comp) {
			T* scary = getComponent<T>(entry);
			if (scary == nullptr) {
				Logger::critical("FATAL: required component access returned nullptr!");
				throw std::exception("FATAL: required component access returned nullptr!");
			}
			comp = scary;
		}


		/**
		 * @brief retrieves multiple components
		 * @details retrieves multiple components by modifying the pointer's 
		 * passed in as the variadic template arguments, as with the function 
		 * above this will throw if any one of the requested components cannot
		 * be found
		 * @tparam ...Comps the types of the components to retrieve
		 * @param entry the actor entry to get the components from
		 * @param ...comps pointers that the retrieved components will be assigned to
		*/
		template<typename... Comps>
		void getComponents(const std::shared_ptr<ActorEntry> entry, Comps*&... comps) {
			int _[] = { 0, ((void)getComponent<Comps>(entry, std::forward<Comps*&>(comps)), 0) ... };
			(void)_;
		}

		/**
		 * @brief removes the specified component from the supplied actor
		 * @tparam T the type of the component to remove
		 * @param entry the actor to remove this component from
		*/
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

		/**
		 * @brief pointer to the scene
		*/
		Scene* scene;

		/**
		 * @brief the component pools that contain all the components for the actors of this scene
		*/
		std::vector<std::shared_ptr<ComponentPool>> componentPools;
	};

	extern int componentCounter;

	/**
	 * @brief gets the id of the specified component
	 * @details component id's are not garunteed to be the same 
	 * across multiple runtimes
	 * @tparam T 
	 * @return 
	*/
	template <class T>
	int getComponentId() {
		static int componentId = componentCounter++;
#ifdef _DEBUG
		static bool printed = false;
		if (!printed) {
			std::string typname = typeid(T).name();
			std::string::size_type i = typname.find("struct");
			if (i != std::string::npos) {
				typname.erase(i, 7);
			}
			i = typname.find("class");
			if (i != std::string::npos) {
				typname.erase(i, 6);
			}
			printed = true;
			Logger::debug("Component {} registered with component ID {}", typname, componentId);
		}
#endif
		return componentId;
	}
}
