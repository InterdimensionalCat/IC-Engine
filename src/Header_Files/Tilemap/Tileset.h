#pragma once
#include "StringableEnum.h"
#include "Texture.h"

namespace ic {

	_CREATE_STRINGABLE_ENUM(TileType, Solid, Air)
	struct TileMetadata {
		uint32_t id;
		TileType type;

		void readFromJson(const json& fileIn);
		void writeToJson(std::shared_ptr<json>& fileOut) const;
	};

	class Tileset {
	public:
		Tileset();
		Tileset(std::string tilesetName);
		Tileset(std::string tilesetName,
			std::unique_ptr<Texture> tilesetTexture,
			std::vector<TileMetadata> metadata,
			size_t tileSizePx,
			size_t numTilesX,
			size_t numTilesY);

		void readFromJson(const std::shared_ptr<json>& fileIn);
		void writeToJson(std::shared_ptr<json>& fileOut) const;

		TileMetadata getMetadata(const uint32_t id);
		Texture& getAtlasTexture();

		size_t getNumTilesX() const {
			return numTilesX;
		}
	private:
		bool loaded;
		std::string tilesetName;
		std::unique_ptr<Texture> tilesetTexture;
		std::vector<TileMetadata> metadata;

		size_t tileSizePx;
		size_t numTilesX;
		size_t numTilesY;
	};
}