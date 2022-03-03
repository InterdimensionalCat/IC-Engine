#include "ActorPool.h"
#include "ActorEntry.h"
#include "Scene.h"
#include "ComponentManager.h"
#include "Components.h"
#include "ActorData.h"

using namespace ic;

ActorPool::ActorPool(GameScene* scene) : scene(scene) {}

ActorPool::~ActorPool() {
	actors.clear();
	freeActors.clear();
}

std::shared_ptr<ActorEntry> ActorPool::spawnActor(const std::string& typeName, const std::string& variantName) {
	if (!freeActors.empty()) {
		auto recycledEntry = freeActors.back();
		freeActors.pop_back();
		recycledEntry->createNewEntry(typeName, variantName);
		return recycledEntry;
	}

	if (maxActors <= actors.size()) {
		maxActors *= 2;

		for (auto& pool : scene->compManager->componentPools) {
			pool->resize(maxActors);
		}
	}

	actors.push_back(std::make_shared<ActorEntry>(actors.size()));
	auto entry = actors.back();
	entry->createNewEntry(typeName, variantName);

	//Logger::get() << entry->getData()->get()->dump(2) << "\n";

	for (auto func : generateFromJsonFunctions) {
		func(scene, entry, entry->getData()->get());
	}

	return entry;
}

std::shared_ptr<ActorEntry> ActorPool::spawnActor(const std::string& typeName, const std::string& variantName, const tmx::Object& object) {
	if (!freeActors.empty()) {
		auto recycledEntry = freeActors.back();
		freeActors.pop_back();
		recycledEntry->createNewEntry(typeName, variantName);
		return recycledEntry;
	}

	if (maxActors <= actors.size()) {
		maxActors *= 2;

		for (auto& pool : scene->compManager->componentPools) {
			pool->resize(maxActors);
		}
	}

	actors.push_back(std::make_shared<ActorEntry>(actors.size()));
	auto entry = actors.back();
	entry->createNewEntry(typeName, variantName, object);

	//Logger::get() << entry->getData()->get()->dump(2) << "\n";

	for (auto func : generateFromJsonFunctions) {
		func(scene, entry, entry->getData()->get());
	}

	return entry;
}

void ActorPool::despawnActor(std::shared_ptr<ActorEntry> entry) {

	Logger::debug("Despawning actor: {}. ", std::to_string(entry->getIndex()));

	if (entry->isRespawnable()) {
		entry->setActive(false);
	}
	else {
		entry->resetEntry();
		for (auto pool : scene->compManager->componentPools) {
			pool->removeComponent(entry->getIndex());
		}
		freeActors.push_back(entry);
	}
}

void ActorPool::respawnActor(std::shared_ptr<ActorEntry> entry) {
	if (!entry->isRespawnable()) {
		return;
	}

	entry->setActive(true);

	for (auto func : generateFromJsonFunctions) {
		func(scene, entry, entry->getData()->get());
	}
}

void ActorPool::saveActorJsonToFile(std::shared_ptr<json> data, const std::string& filename) {
	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "actors";
	filepath /= filename;
	filepath += ".json";

	std::shared_ptr<json> olddata = std::make_shared<json>();

	Logger::info("Saving actor {} to json file.", filename);

	if (fs::exists(filepath)) {
		std::fstream readfile;
		readfile.open(filepath, std::fstream::in);

		try {
			olddata->parse(readfile);
		}
		catch (json::parse_error& e)
		{
			Logger::warn("Exception when parsing existing actor json file {}, exception message: {}."
				, filepath.string(), e.what());
			Logger::warn("Assuming actor {} does not have existing json data.", filename);
		}
	}
	else {
		Logger::info("No existing json data found for actor {}.", filename);
	}

	olddata->update(*data);

	std::ofstream file;
	file.open(filepath, std::ofstream::out);

	file.clear();
	file << olddata->dump(2);
	file.close();
}

std::shared_ptr<json> ActorPool::createJsonFromActor(std::shared_ptr<ActorEntry> entry) {
	std::shared_ptr<json> file = std::make_shared<json>();
	for (auto func : generateJsonFunctions) {
		func(scene, entry, file);
	}
	return file;
}