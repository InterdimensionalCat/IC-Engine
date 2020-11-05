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
	//player = std::make_shared<Player>();
	player = std::make_shared<Player>();
	addActor(static_pointer_cast<Actor>(player));
	//addActor(static_pointer_cast<Actor>(std::make_shared<TestActor>()));
	camera = std::make_shared<Camera>();
	addActor(static_pointer_cast<Actor>(camera));
	start();
}

void Level::addActor(std::shared_ptr<Actor> a) {
	actors.push_back(a);
	a->owner = std::shared_ptr<Level>(this);
}

void Level::removeActor(std::shared_ptr<Actor> a) {
	actors.erase(std::remove_if(actors.begin(), actors.end(), [a](shared_ptr<Actor>& other) {return a.get() == other.get(); }), actors.end());
}

void Level::start() {
	for (auto &a : actors) {
		a->start();
	}
}

void Level::tick(std::shared_ptr<InputHandle>& input) {

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

void Level::draw(std::shared_ptr<Renderer>& renderer) {


	//temporary debug drawing code
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