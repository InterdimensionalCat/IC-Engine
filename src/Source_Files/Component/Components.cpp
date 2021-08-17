#include "include.h"
#include "Components.h"

#include "Scene.h"
#include "ActorEntry.h"

typedef std::function<void(ic::Scene*, std::shared_ptr<ic::ActorEntry>, std::shared_ptr<json>)> Func;

std::vector<Func> ic::generateJsonFunctions = std::vector<Func>();
std::vector<Func> ic::generateFromJsonFunctions = std::vector<Func>();

void ic::registerComponentsFunction() {
	for (auto& compfunc : RegisterComponentsClass::registerComponents) {
		compfunc();
	}

	RegisterComponentsClass::registerComponents.clear();
}

