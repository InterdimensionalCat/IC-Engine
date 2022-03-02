#pragma once
#include "Tile.h"
#include "Texture.h"

namespace ic {

	class Window;

	class Tilemap
	{
	public:
		Tilemap();
		void loadMap(const float widthTiles, const float heightTiles, 
			const std::vector<tmx::TileLayer::Tile>& tiledata, 
			const tmx::Tileset& tileset, const std::string& tilesetName);
		float getWidth() const;
		float getHeight() const;

		void draw(Window& window) const;

		std::vector<Tile> getTilesWithinArea(const sf::FloatRect& hitbox);

	private:
		void setTile(uint32_t x, uint32_t y, const TileMetadata tile);

		void disableInactiveSides();

		//x, y order
		std::vector<std::vector<Tile>> tiles;

		std::unique_ptr<Texture> tileset;

		std::unique_ptr<sf::RenderTexture> rendertex;

		sf::VertexArray vertices;

		//LevelData currentMap;
		float width = 0;
		float height = 0;
	};
}

