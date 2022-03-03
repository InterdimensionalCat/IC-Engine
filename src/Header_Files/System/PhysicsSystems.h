#pragma once
#include "System.h"
#include "Tilemap.h"
#include "TileCollisionEvent.h"
#include "MapBoundCollisionEvent.h"
#include "ComponentManager.h"
#include "Level.h"
#include "SceneEvent.h"
#include "PhysicsSystems.h"

namespace ic {
	class UpdatePositions : public SystemTrivial<Transform, Velocity> {
	public:
		UpdatePositions(GameScene* scene) : SystemTrivial(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			Transform* trans = nullptr;
			Velocity* vel = nullptr;
			scene->compManager->getComponents(entry, trans, vel);

			trans->x += vel->x;
			trans->y += vel->y;
		}
	private:
		_System(UpdatePositions, SystemType::PostPhysics);
	};

	class TilemapCollision : public SystemTrivial<Transform, Velocity, Hitbox, TileCollidable> {
	public:
		TilemapCollision(GameScene* scene) : SystemTrivial<Transform, Velocity, Hitbox, TileCollidable>(scene), tilemap(scene->levels->tilemap) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {

			if (!scene->compManager->getComponent<TileCollidable>(entry)->tileCollidable) {
				return;
			}

			auto trans = scene->compManager->getComponent<Transform>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);
			auto originalhitbox = scene->compManager->getComponent<Hitbox>(entry);

			auto hitbox = getPosSpeedAdjustedHitbox(entry);
			auto tiles = tilemap->getTilesWithinArea(hitbox);
			wallCollision(trans, vel, tiles, hitbox, originalhitbox, entry);
			tiles = tilemap->getTilesWithinArea(hitbox);
			hitbox = getPosSpeedAdjustedHitbox(entry);
			floorCollision(trans, vel, tiles, hitbox, originalhitbox, entry);
			tiles = tilemap->getTilesWithinArea(hitbox);
			hitbox = getPosSpeedAdjustedHitbox(entry);
			ceilingCollision(trans, vel, tiles, hitbox, originalhitbox, entry);

		}
	private:

		void wallCollision(Transform* trans, Velocity* vel,
			const std::vector<Tile>& tiles, const s2d::Rect2m& hitbox,
			const Hitbox* originalhitbox, std::shared_ptr<ActorEntry> entry) {
			if (vel->x == 0) {
				return;
			}

			for (auto& tile : tiles) {

				if (hitbox.min.y + hitbox.height() * 0.2f < tile.getPosY() && tile.isSideActive(Direction::Up)) continue;
				if (hitbox.min.y + hitbox.height() * 0.8f > tile.getPosY() + 1.0f && tile.isSideActive(Direction::Down)) continue;

				if (hitbox.intersects(s2d::Rect2m(tile.getPos(), s2d::Dim2m(1, 1)))) {
					if (vel->x > 0) {
						if (!tile.isSideActive(Direction::Left)) {
							continue;
						}

						auto listener = scene->compManager->getComponent<TileCollisionEventListener>(entry);
						if (listener != nullptr) {
							listener->events->push_back(TileCollisionEvent{ tile, CollisionFace::WallLeft });
						}

						// -> |
						trans->x = tile.getPosX() - originalhitbox->rect.width();
					}
					else {
						if (!tile.isSideActive(Direction::Right)) {
							continue;
						}

						auto listener = scene->compManager->getComponent<TileCollisionEventListener>(entry);
						if (listener != nullptr) {
							listener->events->push_back(TileCollisionEvent{ tile, CollisionFace::WallRight });
						}

						// | <-
						trans->x = tile.getPosX() + 1.0f;
					}
					vel->x = 0.0f;
					return;
				}
			}
		}

		void floorCollision(Transform* trans, Velocity* vel,
			const std::vector<Tile>& tiles, const sf::FloatRect& hitbox,
			const Hitbox* originalhitbox, std::shared_ptr<ActorEntry> entry) {

			if (vel->y <= 0) {
				return;
			}

			for (auto& tile : tiles) {
				if (hitbox.top > tile.getPosY() + 0.2f) continue;
				if (hitbox.top + hitbox.height > tile.getPosY() + 0.8f) continue;

				if (hitbox.intersects(s2d::Rect2m(tile.getPos(), s2d::Dim2m(1, 1)))) {
					if (!tile.isSideActive(Direction::Up)) {
						continue;
					}

					auto listener = scene->compManager->getComponent<TileCollisionEventListener>(entry);
					if (listener != nullptr) {
						listener->events->push_back(TileCollisionEvent{ tile, CollisionFace::Floor });
					}

					trans->y = tile.getPosY() - originalhitbox->rect.height();
					vel->y = 0.0f;
				}
			}
		}

		void ceilingCollision(Transform* trans, Velocity* vel,
			const std::vector<Tile>& tiles, const sf::FloatRect& hitbox,
			const Hitbox* originalhitbox, std::shared_ptr<ActorEntry> entry) {

			if (vel->y >= 0) {
				return;
			}

			for (auto& tile : tiles) {

				if (hitbox.top < tile.getPosY() + 0.2f) continue;
				if (hitbox.top + hitbox.height < tile.getPosY() + 0.8f) continue;

				if (hitbox.intersects(s2d::Rect2m(tile.getPos(), s2d::Dim2m(1, 1)))) {

					if (!tile.isSideActive(Direction::Down)) {
						continue;
					}

					auto listener = scene->compManager->getComponent<TileCollisionEventListener>(entry);
					if (listener != nullptr) {
						listener->events->push_back(TileCollisionEvent{ tile, CollisionFace::Ceiling });
					}

					trans->y = tile.getPosY() + 1.0f;
					vel->y = 0.0f;
					return;
				}
			}
		}

		s2d::Rect2m getPosSpeedAdjustedHitbox(std::shared_ptr<ActorEntry> entry) {
			auto aabbcomp = scene->compManager->getComponent<Hitbox>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);

			auto aabb = aabbcomp->rect;

			aabb += s2d::Vec2m(trans->x, trans->y) + s2d::Vec2m(vel->x, vel->y);

			return aabb;
		}

		std::shared_ptr<Tilemap> tilemap;

		_System(TilemapCollision, SystemType::Physics);
	};

	class ApplyGravity : public SystemTrivial<PhysicsProperties, Velocity> {
	public:
		ApplyGravity(GameScene* scene) : SystemTrivial(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto grv = scene->compManager->getComponent<PhysicsProperties>(entry)->gravity;
			auto vel = scene->compManager->getComponent<Velocity>(entry);
			vel->y += grv;
		}

		_System(ApplyGravity, SystemType::PrePhysics);
	};

	class ApplyFriction : public SystemTrivial<PhysicsProperties, Velocity> {
	public:
		ApplyFriction(GameScene* scene) : SystemTrivial(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {

			auto input = scene->compManager->getComponent<InputController>(entry);

			auto frc = scene->compManager->getComponent<PhysicsProperties>(entry)->friction;
			auto vel = scene->compManager->getComponent<Velocity>(entry);

			if (input != nullptr) {
				auto right = input->input->isDown(InputButton::RIGHT);
				auto left = input->input->isDown(InputButton::LEFT);
				if (right || left && !(right && left)) {
					frc = 1.0f;
				}
			}


			vel->x *= (float)frc;
			if (abs(vel->x) < s2d::toMeters(0.2f)) {
				vel->x = 0;
			}
		}

		_System(ApplyFriction, SystemType::PrePhysics);
	};

	class BindMovement : public SystemTrivial<BoundedVelocity, Velocity> {
	public:
		BindMovement(GameScene* scene) : SystemTrivial(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto mvmt = scene->compManager->getComponent<BoundedVelocity>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);

			if (vel->x > mvmt->maxVelX) {
				vel->x = mvmt->maxVelX;
			}

			if (vel->x < -mvmt->maxVelX) {
				vel->x = -mvmt->maxVelX;
			}

			if (vel->y > mvmt->maxVelY) {
				vel->y = mvmt->maxVelY;
			}

			if (vel->y < -mvmt->maxVelY) {
				vel->y = -mvmt->maxVelY;
			}

		}

		_System(BindMovement, SystemType::Physics);
	};

	class BindPositionByMapBounds : public SystemTrivial<Transform, BoundByMapBounds, Hitbox> {
	public:
		BindPositionByMapBounds(GameScene* scene) : SystemTrivial(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto transform = scene->compManager->getComponent<Transform>(entry);
			auto mapBounds = scene->compManager->getComponent<BoundByMapBounds>(entry);
			auto eventlistener = scene->compManager->getComponent<MapBoundCollisionListener>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);
			auto hitbox = getComponent<Hitbox>(entry)->rect;
			hitbox += s2d::Vec2m(transform->x, transform->y);

			if (mapBounds->boundUp && hitbox.min.y < scene->levels->getUpperBound()) {
				transform->y = s2d::Meters(scene->levels->getUpperBound());
				if (eventlistener != nullptr) {
					eventlistener->events->push_back(MapBoundCollisionEvent::HitUp);
				}

				if (vel != nullptr) {
					vel->y = 0.0f;
				}
			}

			if (mapBounds->boundDown && hitbox.max.y > scene->levels->getLowerBound()) {
				transform->y = s2d::Meters(scene->levels->getLowerBound() - (float)hitbox.height());
				if (eventlistener != nullptr) {
					eventlistener->events->push_back(MapBoundCollisionEvent::HitDown);
				}

				if (vel != nullptr) {
					vel->y = 0.0f;
				}
			}

			if (mapBounds->boundLeft && hitbox.min.x < scene->levels->getLeftBound()) {
				transform->x = s2d::Meters(scene->levels->getLeftBound());
				if (eventlistener != nullptr) {
					eventlistener->events->push_back(MapBoundCollisionEvent::HitLeft);
				}

				if (vel != nullptr) {
					vel->x = 0.0f;
				}
			}

			if (mapBounds->boundRight && hitbox.max.x > scene->levels->getRightBound()) {
				transform->x = s2d::Meters(scene->levels->getRightBound() - (float)hitbox.width());
				if (eventlistener != nullptr) {
					eventlistener->events->push_back(MapBoundCollisionEvent::HitRight);
				}

				if (vel != nullptr) {
					vel->x = 0.0f;
				}
			}
		}

		_System(BindPositionByMapBounds, SystemType::PostUpdate);
	};
}