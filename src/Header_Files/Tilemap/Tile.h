#pragma once
#include "CommonEnum.h"

namespace ic {

	class Tile {
	public:

		Tile();

		Tile(TileMetadata data, 
			const s2d::Meters posX, 
			const s2d::Meters posY);

		bool isSideActive(const Direction& dir) const;

		TileMetadata getMetadata() const;

		s2d::Meters getPosX() const;

		s2d::Meters getPosY() const;

		s2d::Point2m getPos() const;
	private:

		friend class Tilemap;

		TileMetadata data;
		s2d::Point2m pos;
		std::array<bool, 4> activeSides;
	};
}

