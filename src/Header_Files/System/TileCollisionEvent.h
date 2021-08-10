#pragma once
#include "Tile.h"
#include "StringableEnum.h"

namespace ic {
	_CREATE_STRINGABLE_ENUM(CollisionFace, WallLeft, WallRight, Floor, Ceiling);

	struct TileCollisionEvent {
		Tile collidedTile;
		CollisionFace face;
	};
}
