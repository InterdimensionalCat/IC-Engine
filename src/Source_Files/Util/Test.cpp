#include "include.h"
#include "Test.h"
#include "Tileset.h"

using namespace ic::test;


void saveJsonFileUnsafe(std::shared_ptr<json> data, const std::string& filename) {
	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "bin";
	filepath /= filename;
	filepath += ".json";

	ic::Logger::info("Saving {} to json file at {}", filename, filepath.string());
	ic::Logger::info("Existing data will be clobbered");

	std::ofstream file;
	file.open(filepath, std::ofstream::out);

	file.clear();
	file << data->dump(2);
	file.close();
}


void createTilesetJson() {

	auto tilesetName = "astronautTiles";
	auto tilesetTexture = std::make_unique<ic::Texture>(tilesetName);
	size_t tileSizePx = 64;
	size_t numTilesX = 4;
	size_t numTilesY = 4;
	std::vector<ic::TileMetadata> metadata;
	int id = 0;
	for (int i = 0; i < numTilesX; i++) {
		for (int j = 0; j < numTilesY; j++) {
			if (id == 0) {
				metadata.push_back(ic::TileMetadata(id, ic::TileType::Air));
			}
			else {
				metadata.push_back(ic::TileMetadata(id, ic::TileType::Solid));
			}
			id++;
		}
	}
	ic::Tileset test_set(tilesetName, std::move(tilesetTexture), 
		metadata, tileSizePx, numTilesX, numTilesY);

	std::shared_ptr<json> out = std::make_shared<json>();
	test_set.writeToJson(out);
	ic::Logger::debug("Dumping test tileset JSON");
	ic::Logger::debug("{}", out->dump(2));
	saveJsonFileUnsafe(out, "astronautTiles");
}

void ic::test::ProceduralMode() {
	ic::Logger::info("Running in procedural mode: ");
	ic::Logger::info("	-Runs/Tests a certain code snippet then exits");

	createTilesetJson();

	ic::Logger::info("procedural mode exit");
}
