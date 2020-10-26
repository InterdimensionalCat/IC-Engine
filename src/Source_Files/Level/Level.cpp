#include "include.h"
#include "Level.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Actor.h"
#include "testActor.h"
#include "StaticBody.h"
#include "Camera.h"


Level::Level() {

}


void Level::loadFrom(const std::string &mapname) {
	addActor(new Player());
	addActor(new TestActor());
	camera = new Camera();
	addActor(camera);
	start();
}

void Level::addActor(Actor* a) {
	actors.push_back(shared_ptr<Actor>(a));
	if (a->getTag() == "Player") {
		auto pl = dynamic_cast<Player*>(a);
		if (pl) {
			player = pl;
		}
	}
}

void Level::removeActor(Actor* a) {
	actors.erase(std::remove_if(actors.begin(), actors.end(), [a](shared_ptr<Actor>& other) {return a == other.get(); }), actors.end());
}

void Level::start() {
	for (auto &a : actors) {
		a->start();
		Composite* comp = a->getBehavior<Composite>();
		if (comp) {
			comp->Register(engine.get());
		}
	}

	engine->updateSweeper();
}

void Level::tick(InputHandle* input) {

	//player->tick(input);
	engine->updatePhysics(instance->dt);

	for (auto &a : actors) {
		a->tick(input);
	}

	//camera test:
	if (instance->debug) {

	}
	else {
		camera->setPos(player->transform->getPos());
	}
}

void Level::draw(Renderer* renderer) {

	engine->draw(*(renderer->window), renderer->states);

	for (auto &a : actors) {
		a->draw(*(renderer->window), renderer->states);
	}
}