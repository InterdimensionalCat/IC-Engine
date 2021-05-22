//Level.h
/*
  levels are the building blocks of the game, kind of like scene from unity, 
  contains a physics engine, camera, and the Actors needed to make the game function(eventually)
*/
#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "InputHandle.h"
#include "GameEngine2020.h"
#include "Renderer.h"
#include "AudioHandle.h"
#include "ActorUID.h"
#include "RenderVertices.h"
#include "RenderComponent.h"
#include "Component.h"
#include "ComponentFactory.h"

#include <filesystem>
#include <nlohmann\json.hpp>
#include <iostream>
#include "ActorData.h"

#include "MapParser.h"

namespace ic {

	struct ActorShell {
		ActorShell(ActorUID id, std::string name) : id(id), name(name) {}
		ActorUID id;
		std::string name;
	};

	class Scene
	{
	public:
		Scene() {

		}

		void handleInput(InputHandle& input) {}
		void updateAI() {}
		void updatePhysics(const float dt) {}
		void updateAudio(AudioHandle& audio) {}
		void draw(gfx::Renderer& renderer) {}

		void testActorUID() {

			MapParser::parseMap("testmap", *this);
			//auto renderinstance = renderfactory.createNewInstance();
			//loadActorFromJson("test", "test");


			//ActorUID::registerNewActor("player");
			//addActor("player");
			//addActor("player");
			//removeActor(actors.at(0));
			//addActor("player");
			//addActor("player");

		}

		void addActor(std::unique_ptr<nlohmann::json> actormapdata, const std::string& actorname, const std::string& variant = "") {
			ActorData dat(actorname, variant, std::move(actormapdata));
			actors.push_back(dat.getActorUID());
			auto compInstance = renderfactory.createNewInstance(dat);
			if (compInstance.has_value()) {
				rendercomponents.push_back(std::move(compInstance.value()));
			}
		}

		void removeActor(const ActorUID instanceToRemove) {
			actors.erase(std::remove(actors.begin(), actors.end(), instanceToRemove), actors.end());
			//actorshells.erase(std::remove_if(actorshells.begin(), actorshells.end(), [instanceToRemove](const ActorShell& a) {
			//	return a.id == instanceToRemove;
			//	}
			//), actorshells.end());
		}
	private:
		std::vector<ActorUID> actors;
		RenderComponentFactory renderfactory;
		std::vector<std::unique_ptr<RenderComponent>> rendercomponents;
	};
}

