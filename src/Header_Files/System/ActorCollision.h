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
	class ActorCollision : public System {
	public:
		ActorCollision(Scene* scene) : System(scene) {}

		virtual void excecute() {

			BenchmarkLogger::get()->beginBenchmark(this->getName());

			//keep track of the actors in a seperate vector in this system
			//use sweep and prune to reduce calculations

			collidableactors.clear();

			for (auto entry : SceneView<ActorCollidable, Transform, Hitbox>(scene)) {
				collidableactors.push_back(entry);
			}

			for (size_t i = 0; i < collidableactors.size(); i++) {

				for (size_t j = i + 1; j < collidableactors.size(); j++) {
					auto actorA = collidableactors.at(i);
					auto actorB = collidableactors.at(j);

					auto actorCollA = scene->compManager->getComponent<ActorCollidable>(actorA);
					auto actorCollB = scene->compManager->getComponent<ActorCollidable>(actorB);

					auto hitboxA = getPosSpeedAdjustedHitbox(scene, actorA);
					auto hitboxB = getPosSpeedAdjustedHitbox(scene, actorB);


					if (hitboxA.intersects(hitboxB)) {

						auto ABpair = std::pair(actorCollA->collisiontype, actorCollB->collisiontype);
						auto BApair = std::pair(actorCollB->collisiontype, actorCollA->collisiontype);

						auto foundcollfn = collisioncallbackmap.find(ABpair);
						if (foundcollfn != collisioncallbackmap.end()) {
							collisioncallbackmap.at(ABpair)(scene, actorA, actorB);
						}
						else {
							foundcollfn = collisioncallbackmap.find(BApair);
							if (foundcollfn != collisioncallbackmap.end()) {
								collisioncallbackmap.at(BApair)(scene, actorB, actorA);
							}
						}
					}
				}
			}

			BenchmarkLogger::get()->endBenchmark(this->getName());
		}

		std::string toString() const override {
			std::string printval = getName()
				+ ":(System)->Type="
				+ getSysTypeName();
			return printval;
		}


	private:

#ifndef addCollisionFn
#define addCollisionFn(actora, actorb) collisioncallbackmap.emplace(std::pair(#actora, #actorb), actora##to##actorb);
#endif

		class PopulateCallback {
		public:
			PopulateCallback() {
				addCollisionFn(player, enemy);
				addCollisionFn(player, platform);
				addCollisionFn(enemy, platform);
				addCollisionFn(player, goal);
			}
		};

#undef addCollisionFn

		static inline std::map<std::pair<std::string, std::string>, std::function<void(Scene* scene, std::shared_ptr<ActorEntry>, std::shared_ptr<ActorEntry>)>> collisioncallbackmap;

		static inline PopulateCallback popcallback;

		static void playertogoal(Scene* scene, std::shared_ptr<ActorEntry> player, std::shared_ptr<ActorEntry> goal) {
			scene->sceneEvents->pushEvent<ChangeLevelEvent>();
		}

		static void playertoenemy(Scene* scene, std::shared_ptr<ActorEntry> player, std::shared_ptr<ActorEntry> enemy) {


			auto ptrans = scene->compManager->getComponent<Transform>(player);
			auto pvel = scene->compManager->getComponent<Velocity>(player);
			auto phitbox = getPosSpeedAdjustedHitbox(scene, player);
			auto jumpdata = scene->compManager->getComponent<Jumpable>(player);

			auto etrans = scene->compManager->getComponent<Transform>(enemy);
			auto ehitbox = getPosSpeedAdjustedHitbox(scene, enemy);
			auto jumpondata = scene->compManager->getComponent<JumpOn>(enemy);

			auto playerYHigh = ptrans->y;
			auto enemyYHigh = etrans->y;

			if (enemyYHigh - playerYHigh > ehitbox.height() * (float)jumpondata->jumpTolerencePercent) {
				//kill enemy

				jumpdata->jumpedflag = false;

				auto playervely = pvel->y;
				if (playervely > 0) {
					playervely *= -1.0f;
				}
				auto jumpforce = (s2d::Meters)std::min((float)playervely * (float)jumpondata->jumpVelMod, -(float)jumpondata->jumpMin);
				pvel->y = jumpforce;

				scene->sceneEvents->pushEvent<DespawnActorEvent>(enemy);
			}
			else {
				//killplayer
				playerDeath(scene, player);
			}

		}

		static void playertoplatform(Scene* scene, std::shared_ptr<ActorEntry> player, std::shared_ptr<ActorEntry> platform) {
			creatureToPlatform(scene, player, platform);
		}

		static void enemytoplatform(Scene* scene, std::shared_ptr<ActorEntry> enemy, std::shared_ptr<ActorEntry> platform) {
			creatureToPlatform(scene, enemy, platform);
		}

		static void creatureToPlatform(Scene* scene, std::shared_ptr<ActorEntry> creature, std::shared_ptr<ActorEntry> platform) {

			auto cstate = scene->compManager->getComponent<StateController>(creature)->state;
			auto cvel = scene->compManager->getComponent<Velocity>(creature);
			auto chitbox = getPosSpeedAdjustedHitbox(scene, creature);
			auto phitbox = getPosSpeedAdjustedHitboxNoExtension(scene, platform);

			auto cBottomCorner = chitbox.max.y;
			auto pTopCorner = phitbox.min.y;

			if (cstate == ActionState::Airborne) {
				auto caabb = scene->compManager->getComponent<Hitbox>(creature)->rect;
				auto trans = scene->compManager->getComponent<Transform>(creature);

				caabb += s2d::Vec2m(trans->x, trans->y);
				auto cbighitbox = getBoundingBoxOfBoxes(caabb, chitbox);
				//auto cbighitbox = chitbox;
				if (!cbighitbox.intersects(phitbox)) {
					return;
				}
			}
			else {
				if (chitbox.min.y > phitbox.min.y) return;
			}

			auto ptolerence = scene->compManager->getComponent<PlatformTolerence>(platform);
			if (cBottomCorner - ptolerence->down < pTopCorner && cvel->y >= 0) {
				auto ctrans = scene->compManager->getComponent<Transform>(creature);
				auto pvel = scene->compManager->getComponent<Velocity>(platform);
				auto ptype = scene->compManager->getComponent<PlatformTypeable>(platform)->type;
				ctrans->y = phitbox.min.y - chitbox.height();
				//ctrans->y = phitbox.min.y;

				s2d::Meters pgrav;
				auto cgrav = scene->compManager->getComponent<PhysicsProperties>(creature)->gravity;
				
				auto velsignbit = pvel->y < 0 ? -1 : 1;

				switch (ptype) {
				case PlatformType::Horizontal:
					if (cstate == ActionState::Airborne) {
						cvel->x = 0.0f;
					}

					cvel->y = 0.0f;
					ctrans->x += pvel->x;
					break;
				case PlatformType::Vertical:

					if (pvel->y > 0) {
						ctrans->y -= pvel->y;
						cvel->y = pvel->y - cgrav;
					}
					else {
						//cvel->y = pvel->y + ptolerence->up;
						//cvel->y = pvel->y;
						cvel->y = 0;
						//ctrans->y -= pvel->y - ptolerence->up;
					}
					break;
				case PlatformType::Falling:

					pgrav = scene->compManager->getComponent<FallingPlatform>(platform)->grv;

					cvel->y = pvel->y - pgrav;
					scene->compManager->getComponent<FallingPlatform>(platform)->falling = true;
					ctrans->y -= pvel->y;
					cvel->y = pvel->y - pgrav;
					break;
				default:
					cvel->y = 0.0f;
					break;
				}



				auto airbornetimer = scene->compManager->getComponent<AirborneState>(creature);
				airbornetimer->airborneTimer = airbornetimer->maxAirborneTimer;
				if (abs(cvel->x) < s2d::toMeters(0.5f)) {
					scene->compManager->getComponent<StateController>(creature)->state = ActionState::GroundStill;
				}
				else {
					scene->compManager->getComponent<StateController>(creature)->state = ActionState::GroundMove;
				}

				//TODO: FINISH THIS NIGHTMERE XD

				//need to make an actor collision event class and relevant components
			}

		}

		static sf::FloatRect getBoundingBoxOfBoxes(const s2d::Rect2m& A, const s2d::Rect2m& B) {

			auto cmin = s2d::Point2m(std::min(A.min.x, B.min.x), std::min(A.min.y, B.min.y));
			auto cmax = s2d::Point2m(std::max(A.max.x, B.max.x), std::max(A.max.y, B.max.y));

			auto crect = s2d::Rect2m(cmin, cmax);
			return crect;
		}

		static void playerDeath(Scene* scene, std::shared_ptr<ActorEntry> player) {
			scene->sceneEvents->pushEvent<ResetLevelEvent>();
		}

		static s2d::Rect2m getPosSpeedAdjustedHitboxNoExtension(Scene* scene, std::shared_ptr<ActorEntry> entry) {
			auto aabbcomp = scene->compManager->getComponent<Hitbox>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);

			auto aabb = aabbcomp->rect;


			auto veldisp = s2d::Vec2m();

			if (vel != nullptr) {
				veldisp = s2d::Vec2m(vel->x, vel->y);
			}

			aabb += s2d::Vec2m(trans->x, trans->y) + veldisp;

			drawHitbox(scene, aabb);

			return aabb;
		}

		static s2d::Rect2m getPosSpeedAdjustedHitbox(Scene* scene, std::shared_ptr<ActorEntry> entry) {
			auto aabbcomp = scene->compManager->getComponent<Hitbox>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);

			auto aabb = aabbcomp->rect;
			auto displacementvec = s2d::Vec2m();
			auto aabbcompbig = scene->compManager->getComponent<HitboxExtension>(entry);
			if (aabbcompbig != nullptr) {
				aabb = aabbcompbig->rect;

				displacementvec = s2d::Vec2m(aabb.center() - aabbcomp->rect.center());

			}

			auto veldisp = s2d::Vec2m();

			if (vel != nullptr) {
				veldisp = s2d::Vec2m(vel->x, vel->y);
			}
			aabb += s2d::Vec2m(trans->x, trans->y) + veldisp - displacementvec;

			drawHitbox(scene, aabb);

			return aabb;
		}

		static void drawHitbox(Scene* scene, const s2d::Rect2m& rect) {
			sf::RectangleShape shape = rect.makeDrawableSFMLRect(3.0f, sf::Color(0, 0, 0, 0), sf::Color::Red);

			//scene->debugShapes.push_back(shape);
		}

		std::vector<std::shared_ptr<ActorEntry>> collidableactors;

		_System(ActorCollision, SystemType::Physics);
	};
}