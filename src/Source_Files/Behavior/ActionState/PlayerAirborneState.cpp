#include "include.h"
#include "PlayerAirborneState.h"
#include "GameTransform.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "Animator.h"
#include "Animation.h"
#include "PhysicsBody.h"
#include "PhysEventHandler.h"

using namespace s2d;

PlayerAirborneState::PlayerAirborneState() {
	name = "PlayerAirborne";
}

void PlayerAirborneState::init() {

}

void PlayerAirborneState::enter() {

	airaccel = parent->speedValues.at("asp");
	maxVelX = parent->speedValues.at("maxAsp");

	parent->animator->setAnimation(name);
}

void PlayerAirborneState::run(InputHandle* input) {
		if (input->isDown(Keyboard::D)) {
			if (parent->body->getVelocity().x < 0) {
				parent->body->setAwake(true);
				parent->body->addForce(Vec(airaccel * 2.5f, 0));
			}
			else {
				parent->body->setAwake(true);
				parent->body->addForce(Vec(airaccel, 0));
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
				}

				if (parent->body->getVelocity().x < -maxVelX) {
					parent->body->setAwake(true);
					parent->body->setVelocity(Vec(-maxVelX, parent->body->getVelocity().y));
				}
			}
		}

		//check for floor collision
		for (CollisionEvent &c : parent->collisioninfo->events) {

			if (c.normal.y < -0.2f) {
				//hit the ground
				if (abs(parent->body->getVelocity().x) < 0.7 * 60) {
					parent->setState("PlayerIdle", input);
					return;
				}
				else {
					if (abs(parent->body->getVelocity().x) < 5.0 * 60) {
						parent->setState("PlayerMove", input);
						return;
					}
					else {
						parent->setState("PlayerRun", input);
						return;
					}
				}
			}
		}
}

void PlayerAirborneState::draw(Renderer* renderer) {

}

void PlayerAirborneState::exit() {

}