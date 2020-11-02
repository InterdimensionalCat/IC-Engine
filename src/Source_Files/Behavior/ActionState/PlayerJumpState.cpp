#include "include.h"
#include "PlayerJumpState.h"
#include "GameTransform.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "Actor.h"
#include "PhysEventHandler.h"
#include "PhysicsBody.h"
#include "Animator.h"
#include "Animation.h"

using Vec = s2d::GameUnits::Vec;

PlayerJumpState::PlayerJumpState() {
	name = "PlayerJump";
}

void PlayerJumpState::init() {
	//anim.init(Vec(500, 500), Vec(128, 128), "jumpsheet", 23);
}


void PlayerJumpState::enter() {
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vec(0, 0);
	jumpangle = Vec(0, -1);
	velXatJump = parent->body->getVelocity().x;
	parent->animator->setAnimation(name);
}

void PlayerJumpState::run(InputHandle* input) {


	if (parent->animator->current->frameNum < 4) {
		for (auto c : parent->collisioninfo->events) {
			if (c.normal.y < -0.2f) {
				//hit the ground
				jumpangle += c.normal;
				jumpangle = jumpangle.Normalize();
			}
		}
	}
	else {
		if (parent->animator->current->frameNum == 4) {

			//jump
			parent->body->setAwake(true);
			parent->body->setVelocity(Vec(parent->body->getVelocity().x, 0));
			//playerptr->body->addForce(Vec(0, jump));

			parent->body->addForce(Vec(jumpangle.x * (jump + velXatJump), jumpangle.y * jump));
		}
		else {
			if (input->isDown(Keyboard::D)) {
				if (parent->body->getVelocity().x < 0) {
					parent->body->setAwake(true);
					parent->body->addForce(Vec(airaccel * 2.5f, 0));
				}
				else {
					parent->body->setAwake(true);
					parent->body->addForce(Vec(airaccel, 0));
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
						parent->body->addForce(Vec(-airaccel * 2.5f, 0));
					}
					else {
						parent->body->setAwake(true);
						parent->body->addForce(Vec(-airaccel, 0));
						//playerptr->dir = true;
					}

					if (parent->body->getVelocity().x < -maxVelX) {
						parent->body->setAwake(true);
						parent->body->setVelocity(Vec(-maxVelX, parent->body->getVelocity().y));
					}
				}
		    }

			if (!input->isDown(Keyboard::Space)) {
				parent->body->setAwake(true);
				parent->body->setVelocity(Vec(parent->body->getVelocity().x, parent->body->getVelocity().y / 1.06f));
			}

			//check for floor collision
			for (CollisionEvent& c : parent->collisioninfo->events) {

				if (c.normal.y < -0.2f) {
					//hit the ground
					if (abs(parent->body->getVelocity().x) < 0.7 * 60) {
						parent->setState("PlayerIdle", input);
					}
					else {
						if (abs(parent->body->getVelocity().x) < 5.0 * 60) {
							parent->setState("PlayerMove", input);
						}
						else {
							parent->setState("PlayerRun", input);
						}
					}
				}
			}


			//check for airborne transition
			if (parent->animator->current->frameNum == parent->animator->current->numFrames - 1) {
				parent->setState("PlayerAirborne", input);
			}

	    }


	}
}

void PlayerJumpState::draw(Renderer* renderer) {

}

void PlayerJumpState::exit() {

}