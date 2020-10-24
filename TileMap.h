#pragma once
#include "Actor.h"

class Composite;
class Tile;

class TileMap :
	public Actor
{
	virtual string getTag() const { return "Tilemap"; }
	virtual void start();
private:
	Composite* tilecollision;
	int sizex;
	int sizey;
	vector<Tile> tiles;
};

