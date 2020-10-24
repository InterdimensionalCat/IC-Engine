#include "include.h"
#include "PlayerMoveState.h"
#include "GameTransform.h"
#include "Composite.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "Actor.h"



PlayerMoveState::PlayerMoveState() {
	name = "PlayerMove";
}

void PlayerMoveState::init() {

	transform = parent->getActor()->getBehavior<GameTransform>();
	compIn = parent->getActor()->getBehavior<Composite>();

	anim.init(Vector2f(500, 500), Vector2f(128, 128), "walkSsheet");
}

void PlayerMoveState::enter() {
	//set the player as grounded here
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, -10);
	//playerptr->spriteOffset = Vector2f(0, 0);
	framesAir = 0;
}


void PlayerMoveState::run(InputHandle* input) {
	//move if going left, right, can jump from this state
	if (input->isDown(Keyboard::D)) {
		if (compIn->getVelocity().x < 0) {
			//compIn->addForce(Vector2f(groundAccel * 2.5, 0));
			compIn->setVelocity(Vector2f(0, compIn->getVelocity().y));
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
				//compIn->addForce(Vector2f(-groundAccel * 2.5, 0));
				compIn->setVelocity(Vector2f(0, compIn->getVelocity().y));
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

	if (anim.frameNum == anim.numFrames - 1) {
		if (abs(compIn->getVelocity().x) > 5.0f * 60) {
			parent->setState("PlayerRun", input);
		}
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

void PlayerMoveState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	anim.draw(target, states, transform);
}

void PlayerMoveState::exit() {
	framesAir = 0;
	anim.reset();
}