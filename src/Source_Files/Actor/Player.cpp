#include "include.h"
#include "Player.h"
#include "GameTransform.h"
#include "Composite.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerAirborneState.h"
#include "PlayerRunState.h"
#include "RigidBody.h"
#include "ActionStateMap.h"


void Player::start() {

	Vector2f pos = Vector2f(1 * 60, 5 * 60);
	Vector2f size = Vector2f(1 * 60, 1 * 60);

	transform = addBehavior<GameTransform>();
	transform->translate(pos);
	comp = addBehavior<Composite>();
	states = addBehavior<ActionStateMap>();


	RigidBody* b = new RigidBody();
	b->constructQuad(size, pos);
	comp->addBody(b);
	comp->setDensity(1.5);


	states->addState(new PlayerIdleState());
	states->addState(new PlayerMoveState());
	states->addState(new PlayerJumpState());
	states->addState(new PlayerAirborneState());
	states->addState(new PlayerRunState());
	states->setState("PlayerIdle");

	Actor::start();
}

void Player::tick(InputHandle* input) {
	Actor::tick(input);
}