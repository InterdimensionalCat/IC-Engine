#include "include.h"
#include "Player.h"
#include "ActionStateMap.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerAirborneState.h"
#include "PlayerRunState.h"
#include "GameTransform.h"
#include "PhysicsBody.h"
#include "Level.h"
#include "PhysEventHandler.h"
#include "Animator.h"

using namespace s2d;

void Player::start() {

    auto pos = Point(3 * 60.f, 3 * 60.f);
	auto size = Dimension(30, 60);

	auto poly = Poly({ Point(), Point(1,0), Point(1,1), Point(0, 1) }, Rectangle(pos, size));

	transform = addBehavior<GameTransform>();
	transform->translate(Vec(pos.x + 60.f, pos.y + 60.f));
	poly.setCenter(transform->getPos());
	body = addBehavior<PhysicsBody>();
	states = addBehavior<ActionStateMap>();
	animator = addBehavior<Animator>();

	body->setType(CollisionType::Dynamic);
	body->addPoly(poly);
	body->setDensity(1.5f);

	states->start();
	animator->start();


	animator->addAnimation(new Animation(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerIdle", 15, Vector2f(0, -6)));
	animator->addAnimation(new Animation(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerAirborne", 30, Vector2f(0, -8)));
	animator->addAnimation(new Animation(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerJump", 23, Vector2f(0, -8)));
	animator->addAnimation(new Animation(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerMove", 23, Vector2f(0, -8)));
	animator->addAnimation(new Animation(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerRun", 21, Vector2f(0, -20)));

	animator->setAnimation("PlayerIdle");


	states->addState((ActionState*)new PlayerIdleState());
	states->addState((ActionState*)new PlayerMoveState());
	states->addState((ActionState*)new PlayerJumpState());
	states->addState((ActionState*)new PlayerAirborneState());
	states->addState((ActionState*)new PlayerRunState());
	states->setState("PlayerIdle");

	collisioninfo = addBehavior<PhysEventHandler>();

	Actor::start();
}