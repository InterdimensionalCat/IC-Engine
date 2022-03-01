#include "include.h"
#include "Tileset.h"

namespace ic {

    Tileset::Tileset() :
        loaded(false),
        tilesetName("null"),
        tilesetTexture(),
        metadata()
    {

    }
    Tileset::Tileset(std::string tilesetName) :
        loaded(false),
        tilesetName(tilesetName),
        tilesetTexture(),
        metadata()
    {

    }

    Tileset::Tileset(std::string tilesetName,
        std::unique_ptr<Texture> tilesetTexture,
        std::vector<TileMetadata> metadata,
        size_t tileSizePx,
        size_t numTilesX,
        size_t numTilesY) :
        loaded(true),
        tilesetName(tilesetName),
        tilesetTexture(std::move(tilesetTexture)),
        metadata(metadata),
        tileSizePx(tileSizePx),
        numTilesX(numTilesX),
        numTilesY(numTilesY) {}


    void TileMetadata::readFromJson(const json& fileIn) {
        //id
        //type string
        id = fileIn["id"];
        type = TileTypeFromString(fileIn["type"]);
    }
    void TileMetadata::writeToJson(std::shared_ptr<json>& fileOut) const {
        (*fileOut)["id"] = id;
        (*fileOut)["type"] = TileTypeToString(type);
    }

    void Tileset::readFromJson(const std::shared_ptr<json>& fileIn) {
        //name:
        //size px
        //numX
        //numY
        // data arr

        tilesetName = (*fileIn)["tilesetName"];
        tileSizePx = (*fileIn)["tileSizePx"];
        numTilesX = (*fileIn)["numTilesX"];
        numTilesY = (*fileIn)["numTilesY"];
        std::vector<json> entries = (*fileIn)["metadata"];
        for (auto& entry : entries) {
            TileMetadata data;
            data.readFromJson(entry);
            metadata.push_back(data);
        }

        tilesetTexture = std::make_unique<ic::Texture>(tilesetName);
    }

    void Tileset::writeToJson(std::shared_ptr<json>& fileOut) const {
        (*fileOut)["tilesetName"] = tilesetName;
        (*fileOut)["tileSizePx"] = tileSizePx;
        (*fileOut)["numTilesX"] = numTilesX;
        (*fileOut)["numTilesY"] = numTilesY;
        std::vector<json> arr;
        for (auto& data : metadata) {
            std::shared_ptr<json> jdata = std::make_shared<json>();
            data.writeToJson(jdata);
            arr.push_back(*jdata);
        }
        (*fileOut)["metadata"] = arr;
    }

    TileMetadata Tileset::getMetadata(const uint32_t id) {
        if (!loaded) {
            Logger::error("Tileset {} not loaded!", tilesetName);
            throw std::exception();
        }
        return metadata.at(id);
    }
    Texture& Tileset::getAtlasTexture() {
        if (!loaded) {
            Logger::error("Tileset {} not loaded!", tilesetName);
            throw std::exception();
        }

        return *tilesetTexture;
    }
}
