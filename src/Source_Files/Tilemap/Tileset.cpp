#include "include.h"
#include "Tileset.h"

namespace ic;

Tileset::Tileset() : 
    loaded(false), 
    tilesetName("null"),
    tilesetTexture(),
    metadata() 
{

}
Tileset::Tileset(std::string tilesetName, size_t tileSizePx) :
    loaded(false),
    tilesetName(tilesetName),
    tilesetTexture(),
    metadata()
{

}

void TileMetadata::readFromJson(const std::shared_ptr<json>& fileIn) {
    //id
    //type string
    id = (*file)["id"];
    type = TileTypeFromString((*fileIn)["type"]);
}
void TileMetadata::writeToJson(std::shared_ptr<json>& fileOut) const {
    (*file)["id"] = id;
    (*fileIn)["type"] = TileTypeToString(type);
}

void Tileset::readFromJson(const std::shared_ptr<json>& fileIn) {
    //name:
    //size px
    //numX
    //numY
    // data arr

    (*file)["tilesetName"] = tilesetName;
    (*file)["tileSizePx"] = tileSizePx;
    (*file)["numTilesX"] = numTilesX;
    (*file)["numTilesY"] = numTilesY;


}

void Tileset::writeToJson(std::shared_ptr<json>& fileOut) const {

}

TileMetadata Tileset::getMetadata(const uint32_t id) {
    if (!loaded) {
        Logger::error("Tileset {} not loaded!", tilesetName);
        throw std::exception();
    }
    return data;
}
Texture& Tileset::getAtlasTexture() {
    if (!loaded) {
        Logger::error("Tileset {} not loaded!", tilesetName);
        throw std::exception();
    }

    return *tilesetTexture;
}