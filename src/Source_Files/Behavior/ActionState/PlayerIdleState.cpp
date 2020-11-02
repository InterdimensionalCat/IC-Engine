#include "include.h"
#include "PlayerIdleState.h"
#include "GameTransform.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "PhysEventHandler.h"
#include "Animator.h"
#include "Animation.h"

using Vec = s2d::GameUnits::Vec;

PlayerIdleState::PlayerIdleState() {
	name = "PlayerIdle";
}

void PlayerIdleState::init() {
	//anim.init(Vector2f(500, 500), Vector2f(128, 128), "idlesheet", 15);
}


void PlayerIdleState::enter() {
	//set the player as grounded here
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, 0);
	framesAir = 0;
	parent->animator->setAnimation(name);
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
	for (auto &c : parent->collisioninfo->events) {

		if (c.normal.y < -0.2f) {
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

void PlayerIdleState::draw(Renderer* renderer) {

}

void PlayerIdleState::exit() {

}