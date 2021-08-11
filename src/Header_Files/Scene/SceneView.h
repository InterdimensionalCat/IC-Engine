#pragma once

namespace ic {

	class ActorEntry;
	class Scene;


	template<typename... ComponentTypes>
	class SceneView {
	public:
		SceneView(Scene* scene) : scene(scene), all(sizeof...(ComponentTypes) == 0) {
			if (!all) {
				viewComponents = { getComponentId<ComponentTypes>() ... };
			}
		}

		struct Iterator {
			Iterator(Scene* scene, size_t index, const std::vector<int>& viewComponents, bool all)
				: scene(scene), index(index), viewComponents(viewComponents), all(all) {}

			std::shared_ptr<ActorEntry> operator*() const {
				return scene->actorPool->getActor(index);
			}

			std::shared_ptr<ActorEntry> operator*() {
				return scene->actorPool->getActor(index);
			}

			bool operator==(const Iterator& other) const {
				return index == other.index || index == scene->actorPool->size();
			}
			bool operator!=(const Iterator& other) const {
				return index != other.index && index != scene->actorPool->size();
			}

			bool ValidIndex() {
				bool valid = scene->actorPool->getActor(index)->isIdValid() && scene->actorPool->getActor(index)->isActive();
				if (!valid) return valid;
				if (all && valid) return valid;
				for (size_t i = 0; i < viewComponents.size(); i++) {
					if (!scene->actorPool->getActor(index)->hasComponent(viewComponents.at(i))) {
						valid = false;
						break;
					}
				}
				return valid;
			}

			Iterator& operator++() {
				index++;
				while (index < scene->actorPool->size() && !ValidIndex()) {
					index++;
				}
				return *this;
			}


			Scene* scene;
			size_t index;
			std::vector<int> viewComponents;
			bool all;
		};

		const Iterator begin() const {
			if (all) return Iterator(scene, 0, viewComponents, all);
			int index = 0;
			while (index < scene->actorPool->size()) {

				if (!scene->actorPool->getActor(index)->isIdValid() || !scene->actorPool->getActor(index)->isActive()) {
					index++;
					continue;
				}

				bool validFirst = true;
				for (size_t i = 0; i < viewComponents.size(); i++) {
					if (!scene->actorPool->getActor(index)->hasComponent(viewComponents.at(i))) {
						validFirst = false;
						break;
					}
				}

				if (validFirst) {
					break;
				}
				else {
					index++;
				}
			}
			return Iterator(scene, index, viewComponents, all);
		}

		const Iterator end() const
		{
			return Iterator(scene, scene->actorPool->size(), viewComponents, all);
		}

		std::vector<int> viewComponents;
		Scene* scene;
		bool all;
	};
}