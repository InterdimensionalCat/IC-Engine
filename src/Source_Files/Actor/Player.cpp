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
	auto size = Dimension(2 * 60.f, 2 * 60.f);

	auto poly = Poly({ Point(), Point(1,0), Point(1,1), Point(0, 1) }, Rectangle(pos, size));

	transform = addBehavior<GameTransform>();
	transform->translate(Vec(pos.x + 60.f, pos.y + 60.f));
	body = addBehavior<PhysicsBody>();
	states = addBehavior<ActionStateMap>();
	animator = addBehavior<Animator>();

	states->start();
	animator->start();

	body->setType(CollisionType::Dynamic);
	body->addPoly(poly);
	body->setDensity(1.5f);


	animator->addAnimation(std::make_shared<Animation>(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerIdle", 15));
	animator->addAnimation(std::make_shared<Animation>(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerAirborne", 30));
	animator->addAnimation(std::make_shared<Animation>(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerJump", 23));
	animator->addAnimation(std::make_shared<Animation>(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerMove", 23));
	animator->addAnimation(std::make_shared<Animation>(Vector2i(500, 500), Dimension(128.0f, 128.0f), "PlayerRun", 21));

	animator->setAnimation("PlayerIdle");


	states->addState(static_pointer_cast<ActionState>(std::make_shared<PlayerIdleState>()));
	states->addState(static_pointer_cast<ActionState>(std::make_shared<PlayerMoveState>()));
	states->addState(static_pointer_cast<ActionState>(std::make_shared<PlayerJumpState>()));
	states->addState(static_pointer_cast<ActionState>(std::make_shared<PlayerAirborneState>()));
	states->addState(static_pointer_cast<ActionState>(std::make_shared<PlayerRunState>()));
	states->setState("PlayerIdle");

	collisioninfo = addBehavior<PhysEventHandler>();

	Actor::start();
}