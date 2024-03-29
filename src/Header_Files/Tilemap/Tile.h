#pragma once

namespace ic {
	enum class TileType { Solid, Air };

	class TileBase
	{
	public:

		TileBase();

		TileBase(const uint32_t id,
			const TileType type,
			const uint32_t tilesetX,
			const uint32_t tilesetY);

		const uint32_t getID() const;

		const TileType& getType() const;

		const uint32_t getTilesetX() const;

		const uint32_t getTilesetY() const;

	private:

		friend class Tile;

		uint32_t id;
		TileType type;
		uint32_t tilesetX;
		uint32_t tilesetY;
	};

	class Tile {
	public:

		Tile();

		Tile(std::shared_ptr<TileBase> base, const s2d::Meters posX, const s2d::Meters posY);

		bool isLeftActive() const;

		bool isRightActive() const;

		bool isTopActive() const;

		bool isBotActive() const;

		const uint32_t getID() const;

		const TileType& getType() const;

		uint32_t getTilesetX() const;

		uint32_t getTilesetY() const;

		s2d::Meters getPosX() const;

		s2d::Meters getPosY() const;

		s2d::Point2m getPos() const;
	private:

		friend class Tilemap;

		std::shared_ptr<TileBase> base;
		s2d::Point2m pos;
		std::array<bool, 4> activeSides;
	};
}

