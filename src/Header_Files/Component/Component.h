#pragma once
#include "ActorUID.h"
#include <nlohmann\json.hpp>
#include <map>
#include <optional>
#include "ActorData.h"

namespace ic {

	class Component {
	public:
		Component(const ActorData& dat) : componentOwner(dat.getActorUID()) {}
		virtual ~Component() {}
		ActorUID getActor() const { return componentOwner; }
	private:
		ActorUID componentOwner;
	};
}