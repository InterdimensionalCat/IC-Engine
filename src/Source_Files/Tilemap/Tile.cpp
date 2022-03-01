#include "include.h"
#include "Tile.h"
#include "Tileset.h"

using namespace ic;


Tile::Tile() : 
	data(), 
	pos(s2d::Point2m(0, 0)), 
	activeSides({ true, true, true, true }) {}

Tile::Tile(TileMetadata data, 
	const s2d::Meters posX, 
	const s2d::Meters posY) :
	data(data),
	pos(s2d::Point2m(posX, posY)),
	activeSides({ true, true, true, true }) {}


bool Tile::isSideActive(const Direction dir) const {
	using enum Direction;
	switch (dir) {
	case Up:
		return activeSides.at(0);
		break;
	case Down:
		return activeSides.at(2);
		break;
	case Left:
		return activeSides.at(3);
		break;
	case Right:
	default:
		return activeSides.at(1);
	}
}

TileMetadata Tile::getMetadata() const {
	return data;
}

s2d::Meters Tile::getPosX() const {
	return pos.x;
}

s2d::Meters Tile::getPosY() const {
	return pos.y;
}

s2d::Point2m Tile::getPos() const {
	return pos;
}
