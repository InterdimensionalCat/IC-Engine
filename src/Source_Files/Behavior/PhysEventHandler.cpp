#include "PhysEventHandler.h"
#include "Actor.h"
#include "PhysicsEngine.h"
#include "Level.h"



void PhysEventHandler::start() {
	engine = getActor()->owner->engine;
}

void PhysEventHandler::tick(std::shared_ptr<InputHandle>& input) {

}

void PhysEventHandler::draw(std::shared_ptr<Renderer>& renderer) {

}