#include "include.h"
#include "TileMap.h"
#include "Composite.h"
#include "Tile.h"

void TileMap::start() {
	tilecollision = addBehavior<Composite>();
	 Actor::start();
}