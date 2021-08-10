#include "include.h"
#include "SceneEvent.h"
#include "Scene.h"
#include "Level.h"
#include "ActorPool.h"

using namespace ic;

SceneEventManager::~SceneEventManager() {
	while (!preevents.empty()) {
		preevents.pop();
	}

	while (!postevents.empty()) {
		postevents.pop();
	}
}

SceneEventManager::SceneEventManager(Scene* scene) : scene(scene) {}

void ResetLevelEvent::excecute(Scene* scene) {
	scene->levels->loadLevel(scene->levels->getCurrentLevelName());
}

void DespawnActorEvent::excecute(Scene* scene) {
	scene->actorPool->despawnActor(actortodespawn);
}

void ChangeLevelEvent::excecute(Scene* scene) {
	scene->levels->changeLevel();
}

void SceneEventManager::handlePreEvents() {
	std::vector<std::string> excecutedevents;

	while (!preevents.empty()) {

		//TODO: events that are not local to a 
		//specific actor and are scenewide should be 
		//agregated into 1 event call
		if (std::find(excecutedevents.begin(), excecutedevents.end(), preevents.front()->getName())
			== excecutedevents.end()) {

			preevents.front()->excecute(scene);
			excecutedevents.push_back(preevents.front()->getName());
		}
		preevents.pop();
	}
}

void SceneEventManager::handlePostEvents() {
	std::vector<std::string> excecutedevents;

	while (!postevents.empty()) {

		//TODO: events that are not local to a 
		//specific actor and are scenewide should be 
		//agregated into 1 event call
		if (std::find(excecutedevents.begin(), excecutedevents.end(), postevents.front()->getName())
			== excecutedevents.end()) {

			postevents.front()->excecute(scene);
			excecutedevents.push_back(postevents.front()->getName());
		}
		postevents.pop();
	}
}