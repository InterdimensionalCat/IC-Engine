#include "include.h"

#include "Scene.h"
#include "Window.h"


#include "ComponentManager.h"
#include "Level.h"
#include "SystemManager.h"
#include "ActorPool.h"
#include "SceneEvent.h"
#include "Components.h"
#include "TileRegistry.h"
#include "AudioRegistry.h"
#include "AudioEngine.h"
#include "System.h"

#include "BenchmarkLogger.h"

#include "MtSystem.h"

using namespace ic;

Scene::Scene() {

	registerComponentsFunction();

	RegisterTiles();
	RegisterAudio();

	window = std::make_shared<Window>();

	audio = std::make_shared<AudioEngine>();
	
	compManager = std::make_shared<ComponentManager>(this);
	actorPool = std::make_shared<ActorPool>(this);
	sceneEvents = std::make_shared<SceneEventManager>(this);

	levels = std::make_shared<Level>(this);

	sysManager = std::make_shared<SystemManager>(this);

	audio->playMusic("FlatZone", 10.0f);
}

Scene::~Scene() {
	clearAudioRegistry();
}

void Scene::update() {
	BenchmarkLogger::get()->beginBenchmark("SceneUpdate");
	if (!window->updateInput()) {
		Settings::setRunning(false);
		return;
	}

	sceneEvents->handlePreEvents();

	sysManager->runSystemsInRange(SystemType::PreUpdate, SystemType::PreGraphics);

	levels->update();

	sceneEvents->handlePostEvents();
	BenchmarkLogger::get()->endBenchmark("SceneUpdate");
}

void Scene::draw(const float interpol) {
	BenchmarkLogger::get()->beginBenchmark("SceneDraw");
	sysManager->runSystemsInRange(SystemType::PreGraphics, SystemType::Graphics);
	window->preRender(interpol);
	levels->draw(interpol);

	//for (auto& shape : debugShapes) {
		//window->window->draw(shape);
	//}

	//debugShapes.clear();
	sysManager->runSystemsInRange(SystemType::Graphics, SystemType::Count);
	BenchmarkLogger::get()->endBenchmark("SceneDraw");
	window->postRender();
}

