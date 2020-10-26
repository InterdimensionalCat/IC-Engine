#include "include.h"
#include "PlayerIdleState.h"
#include "GameTransform.h"
#include "Composite.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"


PlayerIdleState::PlayerIdleState() {
	name = "PlayerIdle";
}

void PlayerIdleState::init() {

	transform = parent->getActor()->getBehavior<GameTransform>();
	compIn = parent->getActor()->getBehavior<Composite>();

	anim.init(Vector2f(500, 500), Vector2f(128, 128), "idlesheet", 15);
}


void PlayerIdleState::enter() {
	//set the player as grounded here
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, 0);
	framesAir = 0;
}

void PlayerIdleState::run(InputHandle* input) {
	//check if going left, right, jumping
	if (input->isDown(Keyboard::A) || input->isDown(Keyboard::D)) {
		parent->setState("PlayerMove", input);
	}

	if (input->isPressed(Keyboard::Space)) {
		parent->setState("PlayerJump", input);
	}

	bool grounded = false;

	//check for floor collision
	for (auto &c : compIn->collisionInfo) {

		if (c.normal.y > 0.2f) {
			//hit the ground
			grounded = true;
		}
	}

	if (!grounded) {
		framesAir++;
		if (framesAir > maxFramesAir) {
			parent->setState("PlayerAirborne", input);
		}
	}
	else {
		framesAir = 0;
	}


}

void PlayerIdleState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	anim.draw(target, states, transform);
}

void PlayerIdleState::exit() {
	anim.reset();
}