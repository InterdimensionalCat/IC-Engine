#include "include.h"
#include "PlayerRunState.h"
#include "GameTransform.h"
#include "Composite.h"
#include "CollisionEvent.h"
#include "Actor.h"
#include "ActionStateMap.h"


PlayerRunState::PlayerRunState() {
	name = "PlayerRun";
}

void PlayerRunState::init() {

	transform = parent->getActor()->getBehavior<GameTransform>();
	compIn = parent->getActor()->getBehavior<Composite>();

	anim.init(Vector2f(500, 500), Vector2f(128, 128), "walksheet");
}

void PlayerRunState::enter() {
	//set the player as grounded here
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, -10);
	framesAir = 0;
}

void PlayerRunState::run(InputHandle* input) {


	//move if going left, right, can jump from this state
	if (input->isDown(Keyboard::D)) {
		if (compIn->getVelocity().x < 0) {
			compIn->addForce(Vector2f(groundAccel * 2.5, 0));
		}
		else {
			compIn->addForce(Vector2f(groundAccel, 0));
			//playerptr->dir = false;
		}

		if (compIn->getVelocity().x > maxVelX) {
			compIn->setVelocity(Vector2f(maxVelX, compIn->getVelocity().y));
		}
	}
	else {
		if (input->isDown(Keyboard::A)) {
			if (compIn->getVelocity().x > 0) {
				compIn->addForce(Vector2f(-groundAccel * 2.5, 0));
			}
			else {
				compIn->addForce(Vector2f(-groundAccel, 0));
				//playerptr->dir = true;
			}

			if (compIn->getVelocity().x < -maxVelX) {
				compIn->setVelocity(Vector2f(-maxVelX, compIn->getVelocity().y));
			}
		}
		else {

			compIn->setVelocity(Vector2f(compIn->getVelocity().x / 1.05f, compIn->getVelocity().y));

			if (abs(compIn->getVelocity().x) < 0.7 * 60) {
				parent->setState("PlayerIdle", input);
			}
		}
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

	if (anim.frameNum == anim.numFrames - 1) {
		if (abs(compIn->getVelocity().x) < 5.0f * 60) {
			parent->setState("PlayerMove", input);
		}
	}


}

void PlayerRunState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	anim.draw(target, states, transform);
}

void PlayerRunState::exit() {
	framesAir = 0;
	anim.reset();
}