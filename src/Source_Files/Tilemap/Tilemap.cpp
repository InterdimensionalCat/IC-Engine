#include "include.h"
#include "Tilemap.h"
#include "Texture.h"
#include "Image.h"
#include "Window.h"
#include "Tileset.h"

using namespace ic;

Tilemap::Tilemap() : rendertex(std::make_unique<sf::RenderTexture>()) {}

void Tilemap::loadMap(const float widthTiles, const float heightTiles,
    const std::vector<tmx::TileLayer::Tile>& tiledata,
    const tmx::Tileset& tilesetdata, const std::string& tilesetName) {
    width =  widthTiles;
    height = heightTiles;

    rendertex->create((unsigned int)s2d::toPixels(width), (unsigned int)s2d::toPixels(height));

    tiles.resize((size_t)width);
    for (auto& column : tiles) {
        column.resize((size_t)height);
    }

    std::string tilesetname = tilesetdata.getName();
    Tileset set;

    fs::path filepath(fs::current_path());
    filepath /= "resources";
    filepath /= "tilesets";
    filepath /= "meta";
    filepath /= tilesetName;
    filepath += ".json";

    auto tilesetjson = std::make_shared<json>();
    std::ifstream tilesetfile(filepath);

    if (!tilesetfile.is_open()) {
        Logger::error("Error loading tileset data at {}", filepath.string());
        Logger::error("Tileset at {} not found", filepath.string());
        throw std::exception();
    }

    try {
        tilesetfile >> (*tilesetjson);
    }
    catch (json::exception e) {
        Logger::error("Error loading tileset data at {}", filepath.string());
        Logger::error("Error parsing actor data json: {}",
            e.what());
        throw e;
    }

    set.readFromJson(tilesetjson);

    for (size_t i = 0; i < tiledata.size(); i++) {
        auto& tile = tiledata.at(i);
        uint32_t x = (uint32_t)i % (uint32_t)width;
        uint32_t y = (uint32_t)i / (uint32_t)width;
        //Logger::debug("Tile at ({}, {}) is tileId: {}", x, y, tile.ID);
        setTile(x, y, set.getMetadata(tile.ID));
    }

    	tileset = std::make_unique<Texture>(tilesetname);

#pragma warning( push )
#pragma warning( disable : 4244 )

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j)
        {
            sf::Vector2u tileSize = sf::Vector2u((unsigned int)s2d::toPixels(1), (unsigned int)s2d::toPixels(1));

            // get the current tile number
            auto tileAt = tiles.at(i).at(j);

            // find its position in the tileset texture

            auto tilesetX = (tileAt.getTileID() - 1) % set.getNumTilesX();
            auto tilesetY = (tileAt.getTileID() - 1) / set.getNumTilesX();

            //Logger::debug("Tile at ({}, {}) has texcoords: "
            //     "({}, {}) and ID: {}", 
            //    i, j, tilesetX, tilesetY, tileAt.getTileID());

            int tu = tilesetX;
            int tv = tilesetY;

            //int tu = 0;
            //int tv = 0;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        }
    }

#pragma warning( pop )

    disableInactiveSides();

}

void Tilemap::setTile(uint32_t x, uint32_t y, const TileMetadata tile) {
	tiles.at(x).at(y) = Tile(tile, (float)x, (float)y);
}

float Tilemap::getWidth() const {
	return width;
}

float Tilemap::getHeight() const {
	return height;
}

void Tilemap::draw(Window& window) const
{
    // apply the transform
    //window.states.transform *= getTransform();
    rendertex->clear(sf::Color(0,0,0,0));

    sf::RenderStates states = window.states;
    states.texture = &tileset->getTexture();

    rendertex->draw(vertices, states);


    // apply the tileset texture
    //window.states.texture = &tileset->getTexture();



    // draw the vertex array
    //window.window->draw(vertices, window.states);
    rendertex->display();

    window.window->draw(sf::Sprite(rendertex->getTexture()));

    //debug drawing the active sides
    /*for (auto x : tiles) {
        for (auto y : x) {

            if (y.getType() == TileType::Air) continue;

            sf::Vertex top[2];
            top[0].position = sf::Vector2f(toPixels(y.getPosX()), toPixels(y.getPosY()));
            top[1].position = sf::Vector2f(toPixels(y.getPosX() + 1.0f), toPixels(y.getPosY()));

            top[0].color = y.isTopActive() ? sf::Color::White : sf::Color::Black;
            top[1].color = y.isTopActive() ? sf::Color::White : sf::Color::Black;

            sf::Vertex left[2];
            left[0].position = sf::Vector2f(toPixels(y.getPosX()), toPixels(y.getPosY()));
            left[1].position = sf::Vector2f(toPixels(y.getPosX()), toPixels(y.getPosY() + 1.0f));

            left[0].color = y.isLeftActive() ? sf::Color::White : sf::Color::Black;
            left[1].color = y.isLeftActive() ? sf::Color::White : sf::Color::Black;

            sf::Vertex bottom[2];
            bottom[0].position = sf::Vector2f(toPixels(y.getPosX()), toPixels(y.getPosY() + 1.0f));
            bottom[1].position = sf::Vector2f(toPixels(y.getPosX() + 1.0f), toPixels(y.getPosY() + 1.0f));

            bottom[0].color = y.isBotActive() ? sf::Color::White : sf::Color::Black;
            bottom[1].color = y.isBotActive() ? sf::Color::White : sf::Color::Black;

            sf::Vertex right[2];
            right[0].position = sf::Vector2f(toPixels(y.getPosX() + 1.0f), toPixels(y.getPosY()));
            right[1].position = sf::Vector2f(toPixels(y.getPosX() + 1.0f), toPixels(y.getPosY() + 1.0f));

            right[0].color = y.isRightActive() ? sf::Color::White : sf::Color::Black;
            right[1].color = y.isRightActive() ? sf::Color::White : sf::Color::Black;

            window.window->draw(top, 2, sf::PrimitiveType::Lines);
            window.window->draw(right, 2, sf::PrimitiveType::Lines);
            window.window->draw(bottom, 2, sf::PrimitiveType::Lines);
            window.window->draw(left, 2, sf::PrimitiveType::Lines);
        }
    }*/

}

void Tilemap::disableInactiveSides() {
    for (int x = 0; x < tiles.size(); x++) {
        for (int y = 0; y < tiles.at(0).size(); y++) {

            auto& currentTile = tiles.at(x).at(y);

            if (y > 0) {
                auto& topTile = tiles.at(x).at(y - 1);
                if (topTile.getType() == TileType::Solid) {
                    currentTile.activeSides.at(0) = false;
                }
            }

            if ((y-1) >= tiles.at(x).size()) {
                auto& botTile = tiles.at(x).at(y + 1);
                if (botTile.getType() == TileType::Solid) {
                    currentTile.activeSides.at(2) = false;
                }
            }

            if ((x - 1) >= tiles.size()) {
                auto& rightTile = tiles.at(x + 1).at(y);
                if (rightTile.getType() == TileType::Solid) {
                    currentTile.activeSides.at(1) = false;
                }
            }

            if (x > 0) {
                auto& leftTile = tiles.at(x - 1).at(y);
                if (leftTile.getType() == TileType::Solid) {
                    currentTile.activeSides.at(3) = false;
                }
            }

        }
    }
}

std::vector<Tile> Tilemap::getTilesWithinArea(const sf::FloatRect& hitbox) {
    std::vector<Tile> returntiles;


    size_t startX = (size_t)abs(floor(hitbox.left));
    size_t startY = (size_t)abs(floor(hitbox.top));

    if (startX > 0) startX -= 1;
    if (startY > 0) startY -= 1;

    size_t endX = (size_t)abs(ceil(hitbox.left + hitbox.width)) + 1;
    size_t endY = (size_t)abs(ceil(hitbox.top + hitbox.height)) + 1;

    returntiles.reserve((endX - startX + 1) * (endY - startY + 1));

    for (size_t x = startX; x < endX && x < tiles.size(); x++) {
        for (size_t y = startY; y < endY && y < tiles.at(0).size(); y++) {
            auto tile = tiles.at(x).at(y);
            auto tileAABB = sf::FloatRect(tile.pos, sf::Vector2f(1.0f, 1.0f));
            if (hitbox.intersects(tileAABB) && tile.getType() == TileType::Solid) {
                returntiles.push_back(tile);
            }
        }
    }

    return returntiles;

    //for (auto& x : tiles) {
    //    for (auto& y : x) {
    //        if(y.getType() != TileType::Air)
    //        returntiles.push_back(y);
    //    }
    //}

    //return returntiles;
}

