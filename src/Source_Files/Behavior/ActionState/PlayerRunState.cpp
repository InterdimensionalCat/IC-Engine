#include "include.h"
#include "PlayerRunState.h"
#include "GameTransform.h"
#include "CollisionEvent.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "PhysEventHandler.h"
#include "PhysicsBody.h"
#include "Animator.h"
#include "Animation.h"

using namespace s2d;

PlayerRunState::PlayerRunState() {
	name = "PlayerRun";
}

void PlayerRunState::init() {

}

void PlayerRunState::enter() {

	groundAccel = parent->speedValues.at("gsp");
	maxVelX = parent->speedValues.at("maxGsp");

	framesAir = 0;
	parent->animator->setAnimation(name);
}

void PlayerRunState::run(InputHandle* input) {


	//move if going left, right, can jump from this state
	if (input->isDown(Keyboard::D)) {
		if (parent->body->getVelocity().x < 0) {
			parent->body->setAwake(true);
			parent->body->addForce(Vec(groundAccel * 2.5f, 0));
		}
		else {
			parent->body->setAwake(true);
			parent->body->addForce(Vec(groundAccel, 0));
			//playerptr->dir = false;
		}

		if (parent->body->getVelocity().x > maxVelX) {
			parent->body->setAwake(true);
			parent->body->setVelocity(Vec(maxVelX, parent->body->getVelocity().y));
		}
	}
	else {
		if (input->isDown(Keyboard::A)) {
			if (parent->body->getVelocity().x > 0) {
				parent->body->setAwake(true);
				parent->body->addForce(Vec(-groundAccel * 2.5f, 0));
			}
			else {
				parent->body->setAwake(true);
				parent->body->addForce(Vec(-groundAccel, 0));
				//playerptr->dir = true;
			}

			if (parent->body->getVelocity().x < -maxVelX) {
				parent->body->setAwake(true);
				parent->body->setVelocity(Vec(-maxVelX, parent->body->getVelocity().y));
			}
		}
		else {

			parent->body->setAwake(true);
			parent->body->setVelocity(Vec(parent->body->getVelocity().x / 1.05f, parent->body->getVelocity().y));

			if (abs(parent->body->getVelocity().x) < 0.7 * 60) {
				parent->setState("PlayerIdle", input);
				return;
			}
		}
	}


	if (input->isPressed(Keyboard::Space)) {
		parent->setState("PlayerJump", input);
		return;
	}

	bool grounded = false;

	//check for floor collision
	for (auto& c : parent->collisioninfo->events) {

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

	if (parent->animator->current->frameNum == parent->animator->current->numFrames - 1) {
		if (abs(parent->body->getVelocity().x) < 5.0f * 60) {
			parent->setState("PlayerMove", input);
			return;
		}
	}


}

void PlayerRunState::draw(Renderer* renderer) {

}

void PlayerRunState::exit() {
	framesAir = 0;
}