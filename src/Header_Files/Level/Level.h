//Level.h
/*
  levels are the building blocks of the game, kind of like scene from unity, 
  contains a physics engine, camera, and the Actors needed to make the game function(eventually)
*/
#pragma once
#include "PhysicsEngine.h"

class Player;
class PhysicsBody;
class Actor;
class Camera;

class Level
{
public:
	Level();

	void tick(InputHandle* input);
	void draw(Renderer* renderer);

	void loadFrom(const std::string &mapname);
	void addActor(Actor* a);
	void removeActor(Actor* a);
	void start();

	Camera* camera;
	Player* player;
	std::unique_ptr<PhysicsEngine> engine = std::make_unique<PhysicsEngine>();
	std::vector<PhysicsBody*> bodies;
	std::vector<std::shared_ptr<Actor>> actors;
};

