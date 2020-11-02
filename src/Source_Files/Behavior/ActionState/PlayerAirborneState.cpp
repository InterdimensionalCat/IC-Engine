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

using Vec = s2d::GameUnits::Vec;

PlayerAirborneState::PlayerAirborneState() {
	name = "PlayerAirborne";
}

void PlayerAirborneState::init() {
	//anim.init(Vector2f(500, 500), Vector2f(128, 128), "airbornesheet", 30);
}

void PlayerAirborneState::enter() {
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
}

void PlayerAirborneState::draw(Renderer* renderer) {

}

void PlayerAirborneState::exit() {

}