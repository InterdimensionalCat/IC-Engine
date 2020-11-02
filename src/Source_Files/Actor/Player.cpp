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

using Point = s2d::GameUnits::Point;
using Vec = s2d::GameUnits::Vec;

using pDimension = s2d::PixelUnits::Dimension;

void Player::start() {

    auto pos = Point(3, 3);
	auto size = s2d::GameUnits::Dimension(2, 2);

	auto poly = s2d::GameUnits::Poly({ Point(), Point(1,0), Point(1,1), Point(0, 1) }, s2d::GameUnits::Rectangle(pos, size));

	transform = addBehavior<GameTransform>();
	transform->translate(Vec(pos.x + 1.0f, pos.y + 1.0f));
	body = addBehavior<PhysicsBody>();
	states = addBehavior<ActionStateMap>();
	animator = addBehavior<Animator>();

	states->start();
	animator->start();

	body->setType(CollisionType::Dynamic);
	body->addPoly(poly);
	body->setDensity(1.5f);


	animator->addAnimation(new Animation(Vector2i(500, 500), pDimension(128.0f, 128.0f), "PlayerIdle", 15));
	animator->addAnimation(new Animation(Vector2i(500, 500), pDimension(128.0f, 128.0f), "PlayerAirborne", 30));
	animator->addAnimation(new Animation(Vector2i(500, 500), pDimension(128.0f, 128.0f), "PlayerJump", 23));
	animator->addAnimation(new Animation(Vector2i(500, 500), pDimension(128.0f, 128.0f), "PlayerMove", 23));
	animator->addAnimation(new Animation(Vector2i(500, 500), pDimension(128.0f, 128.0f), "PlayerRun", 21));

	animator->setAnimation("PlayerIdle");


	states->addState(new PlayerIdleState());
	states->addState(new PlayerMoveState());
	states->addState(new PlayerJumpState());
	states->addState(new PlayerAirborneState());
	states->addState(new PlayerRunState());
	states->setState("PlayerIdle");

	collisioninfo = addBehavior<PhysEventHandler>();

	Actor::start();
}