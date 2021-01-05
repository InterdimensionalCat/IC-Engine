//Level.h
/*
  levels are the building blocks of the game, kind of like scene from unity, 
  contains a physics engine, camera, and the Actors needed to make the game function(eventually)
*/
#pragma once
#include "InputHandle.h"
#include "Renderer.h"
#include "AudioHandle.h"

namespace ic {
	class Scene
	{
	public:
		Scene() {}

		void handleInput(InputHandle& input) {}
		void updateAI() {}
		void updatePhysics(const float dt) {}
		void updateAudio(AudioHandle& audio) {}
		void draw(Renderer& renderer) {}

		//void loadFrom(const std::string& mapname) {}
		//void addActor(Actor* a) {}
		//void removeActor(Actor* a) {}

		//std::unique_ptr<PhysicsEngine> engine = std::make_unique<PhysicsEngine>();
	};
}

