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

	void tick(std::shared_ptr<InputHandle>& input);
	void draw(std::shared_ptr<Renderer>& renderer);

	void loadFrom(const std::string &mapname);
	void addActor(std::shared_ptr<Actor> a);
	void removeActor(std::shared_ptr<Actor> a);
	void start();

	std::shared_ptr<Camera> camera = std::shared_ptr<Camera>(nullptr);
	std::shared_ptr<Player> player = std::shared_ptr<Player>(nullptr);
	std::shared_ptr<PhysicsEngine> engine = std::make_shared<PhysicsEngine>();
	std::vector<std::shared_ptr<PhysicsBody>> bodies;
	std::vector<std::shared_ptr<Actor>> actors;
};

