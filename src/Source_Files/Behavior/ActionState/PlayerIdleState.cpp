#include "include.h"
#include "PlayerIdleState.h"
#include "GameTransform.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "PhysEventHandler.h"
#include "Animator.h"
#include "Animation.h"

using namespace s2d;

PlayerIdleState::PlayerIdleState() {
	name = "PlayerIdle";
}

void PlayerIdleState::init() {

}

void PlayerIdleState::enter() {

	framesAir = 0;
	parent->animator->setAnimation(name);
}

void PlayerIdleState::run(InputHandle* input) {
	//check if going left, right, jumping
	if (input->isDown(Keyboard::A) || input->isDown(Keyboard::D)) {
		parent->setState("PlayerMove", input);
		return;
	}

	if (input->isPressed(Keyboard::Space)) {
		parent->setState("PlayerJump", input);
		return;
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
			return;
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