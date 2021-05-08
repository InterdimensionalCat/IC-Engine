#pragma once
#include <map>
#include "Component.h"
#include "ActorUID.h"
#include <optional>
#include <memory>

namespace ic {

	class RenderComponent;

	template<typename T>
	class ComponentFactory {
	public:
		virtual std::optional<std::unique_ptr<T>> createNewInstance(const ActorData& dat) = 0;
	};

	class RenderComponentFactory : public ComponentFactory<RenderComponent> {
	public:
		std::optional<std::unique_ptr<RenderComponent>> createNewInstance(const ActorData& dat);
	};
}