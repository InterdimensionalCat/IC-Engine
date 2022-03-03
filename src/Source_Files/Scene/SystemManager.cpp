#include "SystemManager.h"
#include "System.h"

#include "PhysicsSystems.h"
#include "GraphicsSystems.h"
#include "InputSystems.h"
#include "ActorCollision.h"
#include "DebugGraphics.h"

using namespace ic;

SystemManager::SystemManager(GameScene* scene) : scene(scene) {
	for (auto& [name, id] : System::nameidmap) {
		systems.push_back(std::move(System::createSystem(scene, name)));
	}

	std::sort(systems.begin(), systems.end(), [](const auto a, const auto b) {
		return a->getType() < b->getType();
		}
	);

	for (auto system : systems) {
		Logger::info("Successfully loaded System:\n    {}", system->toString());
	}
}

void SystemManager::runSystemsInRange(const SystemType begin, const SystemType end) {
	auto beginitr = std::find_if(systems.begin(), systems.end(), [begin](const auto a) {
		return (a->getType() >= begin);
		});
	auto enditr = std::find_if(systems.begin(), systems.end(), [end](const auto a) {
		return (a->getType() >= end);
		});

	for (; beginitr != enditr; beginitr++) {
		beginitr->get()->excecute();
	}

	//std::for_each(beginitr, enditr,
	//	[](auto a) {
	//		a->excecute();
	//	}
	//);
}