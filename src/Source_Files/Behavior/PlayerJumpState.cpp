#include "include.h"
#include "PlayerJumpState.h"
#include "GameTransform.h"
#include "Composite.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"
#include "Actor.h"


PlayerJumpState::PlayerJumpState() {
	name = "PlayerJump";
}

void PlayerJumpState::init() {

	transform = parent->getActor()->getBehavior<GameTransform>();
	compIn = parent->getActor()->getBehavior<Composite>();

	anim.init(Vector2f(500, 500), Vector2f(128, 128), "jumpsheet", 23);
}


void PlayerJumpState::enter() {
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, 0);
	jumpangle = Vector2f(0, 1);
	velXatJump = compIn->getVelocity().x;
}

void PlayerJumpState::run(InputHandle* input) {


	if (anim.frameNum < 4) {
		for (auto c : compIn->collisionInfo) {
			if (c.normal.y > 0.2f) {
				//hit the ground
				jumpangle += c.normal;
				jumpangle = VecNormalize(jumpangle);
			}
		}
	}
	else {
		if (anim.frameNum == 4) {

			//jump
			compIn->setVelocity(Vector2f(compIn->getVelocity().x, 0));
			//playerptr->body->addForce(Vector2f(0, jump));

			compIn->addForce(Vector2f(jumpangle.x * (jump + velXatJump), jumpangle.y * jump));
		}
		else {
			if (input->isDown(Keyboard::D)) {
				if (compIn->getVelocity().x < 0) {
					compIn->addForce(Vector2f(airaccel * 2.5f, 0));
				}
				else {
					compIn->addForce(Vector2f(airaccel, 0));
					//playerptr->dir = false;
				}

				if (compIn->getVelocity().x > maxVelX) {
					compIn->setVelocity(Vector2f(maxVelX, compIn->getVelocity().y));
				}
			}
			else {
				if (input->isDown(Keyboard::A)) {
					if (compIn->getVelocity().x > 0) {
						compIn->addForce(Vector2f(-airaccel * 2.5f, 0));
					}
					else {
						compIn->addForce(Vector2f(-airaccel, 0));
						//playerptr->dir = true;
					}

					if (compIn->getVelocity().x < -maxVelX) {
						compIn->setVelocity(Vector2f(-maxVelX, compIn->getVelocity().y));
					}
				}
		    }

			if (!input->isDown(Keyboard::Space)) {
				compIn->setVelocity(Vector2f(compIn->getVelocity().x, compIn->getVelocity().y / 1.06f));
			}

			//check for floor collision
			for (auto c : compIn->collisionInfo) {
				if (c.normal.y > 0.2f) {
					//hit the ground
					if (abs(compIn->getVelocity ().x) < 0.7 * 60) {
						parent->setState("PlayerIdle", input);
					}
					else {
						if (abs(compIn->getVelocity().x) < 5.0 * 60) {
							parent->setState("PlayerMove", input);
						}
						else {
							parent->setState("PlayerRun", input);
						}
					}
				}
			}


			//check for airborne transition
			if (anim.frameNum == anim.numFrames - 1) {
				parent->setState("PlayerAirborne", input);
			}

	    }


	}
}

void PlayerJumpState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	anim.draw(target, states, transform);
}

void PlayerJumpState::exit() {
	anim.reset();
}