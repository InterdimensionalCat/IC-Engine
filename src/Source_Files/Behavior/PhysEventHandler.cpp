#include "PhysEventHandler.h"
#include "Actor.h"
#include "PhysicsEngine.h"
#include "Level.h"



void PhysEventHandler::start() {
	engine = getActor()->owner->engine.get();
}

void PhysEventHandler::tick(InputHandle* input) {

}

void PhysEventHandler::draw(Renderer* renderer) {

}