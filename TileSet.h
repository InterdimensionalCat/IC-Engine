#pragma once
#include "Tile.h"
#include "Actor.h"

class GameTransform;
class Composite;

class TileSet :
	public Actor
{
public:
	TileSet(const std::string &filename);
	TileSet();
	void start();
	void tick() {}
	string getTag() const { return "Tileset"; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	unique_ptr<sf::Texture> texture;
	unique_ptr < sf::RenderTexture> rendertex;
	unique_ptr < sf::RenderTexture> hitboxtex;
	sf::VertexBuffer buffer;
	int sizex;
	int sizey;
	int tilesize;
	vector<vector<Tile>> tiles;
	std::string filename;

	Composite* testcomp;
	GameTransform* testtransform;
};

