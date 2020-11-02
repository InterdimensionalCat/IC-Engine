#include "include.h"
#include "Level.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Actor.h"
#include "testActor.h"
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
	a->owner = this;
}

void Level::removeActor(Actor* a) {
	actors.erase(std::remove_if(actors.begin(), actors.end(), [a](shared_ptr<Actor>& other) {return a == other.get(); }), actors.end());
}

void Level::start() {
	for (auto &a : actors) {
		a->start();
	}
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
		//camera->setPos(player->transform->getPos());
	}
}

void Level::draw(Renderer* renderer) {

	for (int i = 0; i < 45; i++) {
		sf::Vertex line[2];
		line[0].position = Vector2f(i * 60.0f, 0.0f);
		line[1].position = Vector2f(i * 60.0f, 45 * 60.0f);
		line[0].color = sf::Color(255, 0, 0, 255);
		line[1].color = sf::Color(0, 0, 255, 255);
		renderer->window->draw(line, 2, Lines);
	}

	for (int i = 0; i < 45; i++) {
		sf::Vertex line[2];
		line[0].position = Vector2f(0.0f, i * 60.0f);
		line[1].position = Vector2f(45 * 60.0f, i * 60.0f);
		line[0].color = sf::Color(255, 0, 0, 255);
		line[1].color = sf::Color(0, 0, 255, 255);
		renderer->window->draw(line, 2, Lines);
	}

	for (auto &a : actors) {
		a->draw(renderer);
	}
}