//Level.h
/*
  levels are the building blocks of the game, kind of like scene from unity, 
  contains a physics engine, camera, and the Actors needed to make the game function(eventually)
*/
#pragma once
#include <vector>
#include <memory>
#include "InputHandle.h"
#include "GameEngine2020.h"
#include "Renderer.h"
#include "AudioHandle.h"
#include "ActorUID.h"

namespace ic {

	struct ActorShell {
		ActorShell(ActorUID id, std::string name) : id(id), name(name) {}
		ActorUID id;
		std::string name;
	};

	class Scene
	{
	public:
		Scene() {}

		void handleInput(InputHandle& input) {}
		void updateAI() {}
		void updatePhysics(const float dt) {}
		void updateAudio(AudioHandle& audio) {}
		void draw(gfx::Renderer& renderer) {}

		void testActorUID() {
			ActorUID::registerNewActor("player");
			addActor("player");
			addActor("player");
			removeActor(actors.at(0));
			addActor("player");
			addActor("player");

		}

		//void loadFrom(const std::string& mapname) {}
		//void addActor(Actor* a) {}
		//void removeActor(Actor* a) {}

		//std::unique_ptr<PhysicsEngine> engine = std::make_unique<PhysicsEngine>();
		std::vector<ActorUID> actors;
		std::vector<ActorShell> actorshells;

		void addActor(const std::string& name) {
			auto uid = ActorUID::createNewInstance(name);
			actors.push_back(uid);
			actorshells.push_back(ActorShell(uid, name));
		}

		void removeActor(const ActorUID instanceToRemove) {
			actors.erase(std::remove(actors.begin(), actors.end(), instanceToRemove), actors.end());
			actorshells.erase(std::remove_if(actorshells.begin(), actorshells.end(), [instanceToRemove](const ActorShell& a) {
				return a.id == instanceToRemove;
				}
			), actorshells.end());
		}

	};
}

