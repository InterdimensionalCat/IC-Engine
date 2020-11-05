#include "include.h"
#include "Behavior.h"
#include "Actor.h"

std::shared_ptr<Actor> Behavior::getActor() {
	return parent;
}
