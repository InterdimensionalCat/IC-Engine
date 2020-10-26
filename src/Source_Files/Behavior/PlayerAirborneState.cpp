#include "include.h"
#include "PlayerAirborneState.h"
#include "Composite.h"
#include "GameTransform.h"
#include "Actor.h"
#include "ActionStateMap.h"
#include "CollisionEvent.h"

PlayerAirborneState::PlayerAirborneState() {
	name = "PlayerAirborne";
}

void PlayerAirborneState::init() {

	transform = parent->getActor()->getBehavior<GameTransform>();
	compIn = parent->getActor()->getBehavior<Composite>();

	anim.init(Vector2f(500, 500), Vector2f(128, 128), "airbornesheet", 30);
}

void PlayerAirborneState::enter() {
	//playerptr->animptr = &anim;
	//playerptr->spriteOffset = Vector2f(0, 0);
}

void PlayerAirborneState::run(InputHandle* input) {
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

		//check for floor collision
		for (auto &c : compIn->collisionInfo) {

			if (c.normal.y > 0.2f) {
				//hit the ground
				if (abs(compIn->getVelocity().x) < 0.7 * 60) {
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
}

void PlayerAirborneState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	anim.draw(target, states, transform);
}

void PlayerAirborneState::exit() {
	anim.reset();
}