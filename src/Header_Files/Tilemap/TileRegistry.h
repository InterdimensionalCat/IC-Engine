#pragma once

namespace ic {
	struct TileMetadata;

	void RegisterTiles();
	const TileMetadata getTileFromID(const sf::Color id);
	const TileMetadata getTileFromID(const uint32_t id);
	const TileMetadata getTileFromID(const uint8_t red,
		const uint8_t green,
		const uint8_t blue,
		const uint8_t alpha);

}