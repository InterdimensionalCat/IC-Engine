#include "ComponentFactory.h"
#include "RenderComponent.h"
#include "RenderVertices.h"
#include "ActorUID.h"
#include <optional>
#include <memory>
#include <string>

using namespace ic;

std::optional<std::unique_ptr<ic::RenderComponent>> RenderComponentFactory::createNewInstance(const ActorData& dat) {
	if (dat.getActorName() == "RenderVertices") {
		return std::move(std::make_unique<RenderVertices>(dat));
	}



	return {};
}