#include "MapParser.h"
#include "Scene.h"
#include "tileson\tileson.hpp"
#include "LoggerProvider.h"
#include <exception>


using namespace ic;

void MapParser::parseMap(const std::string& mapName, Scene& scene) {


	std::filesystem::path mappath(std::filesystem::current_path());
	mappath /= "resources";
	mappath /= "maps";
	mappath /= mapName;
	mappath += ".json";

	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(mappath);

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		for (auto& layer : map->getLayers())
		{
			if (layer.getType() == tson::LayerType::ObjectGroup)
			{
				for (auto& obj : layer.getObjects())
				{

					std::unique_ptr<nlohmann::json> mapjson = std::make_unique<nlohmann::json>();

					//Just iterate through all the objects
					auto objproperties = obj.getProperties();
					auto actorname = obj.getProp("actorname")->getValue()._Cast<std::string>();
					auto variantname = obj.getProp("variantname")->getValue()._Cast<std::string>();
					auto pos = obj.getPosition();
					mapjson->operator[]("posx")= pos.x;
					mapjson->operator[]("posy") = pos.y;
					for (auto& [key, val] : objproperties.getProperties()) {
						if (val.getValueType().name() == typeid(std::string).name()) {
							auto typedval = val.getValue()._Cast<std::string>();
							mapjson->operator[](key) = *typedval;
						}

						if (val.getValueType().name() == typeid(float).name()) {\
							auto typedval = val.getValue()._Cast<float>();
						mapjson->operator[](key) = *typedval;
						}

						if (val.getValueType().name() == typeid(int).name()) {
							auto typedval = val.getValue()._Cast<int>();
							mapjson->operator[](key) = *typedval;
						}
					}

					scene.addActor(std::move(mapjson), *actorname, *variantname);
				}
			}
		}
	}
	else //Error occured
	{
		LoggerProvider::log("Map loading error occured: " + map->getStatusMessage(), LogSeverity::Fatal, LogType::General);
		throw std::exception();
	}

}
/*
std::filesystem::path mappath(std::filesystem::current_path());
	mappath /= "resources";
	mappath /= "map";
	mappath /= mapName;
	mappath += ".json";

	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(mappath);

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		//Get color as an rgba color object
		tson::Colori bgColor = map->getBackgroundColor(); //RGBA with 0-255 on each channel

		//This color can be compared with Tiled hex string
		if (bgColor == "#ffaa07")
			printf("Cool!");

		//Or you can compare them with other colors
		tson::Colori otherColor{ 255, 170, 7, 255 };
		if (bgColor == otherColor)
			printf("This works, too!");

		//You can also get the color as float, transforming values if they are already in their int form, from max 255 to 1.f
		tson::Colorf bgColorFloat = bgColor.asFloat();

		//Or the other way around
		tson::Colori newBg = bgColorFloat.asInt();

		//You can loop through every container of objects
		for (auto& layer : map->getLayers())
		{
			if (layer.getType() == tson::LayerType::ObjectGroup)
			{
				for (auto& obj : layer.getObjects())
				{
					//Just iterate through all the objects
				}
				//Or use these queries:

				//Gets the first object it finds with the name specified
				tson::Object* player = layer.firstObj("player"); //Does not exist in demo map->..

				//Gets all objects with a matching name
				std::vector<tson::Object> enemies = layer.getObjectsByName("goomba"); //But we got two of those

				//Gets all objects of a specific type
				std::vector<tson::Object> objects = layer.getObjectsByType(tson::ObjectType::Object);

				//Gets an unique object by its name.
				tson::Object* uniqueObj = layer.getObj(2);
			}
		}

		//Or get a specific object if you know its name (or id)
		tson::Layer* layer = map->getLayer("Main Layer");
		tson::Tileset* tileset = map->getTileset("demo-tileset");
		tson::Tile* tile = tileset->getTile(1); //Tileson tile-IDs starts with 1, to be consistent
		// with IDs in data lists. This is in other words the
		//first tile.

		//For tile layers, you can get the tiles presented as a 2D map by calling getTileData()
		//Using x and y positions in tile units.
		if (layer->getType() == tson::LayerType::TileLayer)
		{
			//When the map is of a fixed size, you can get the tiles like this
			if (!map->isInfinite())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = layer->getTileData();

				//Unsafe way to get a tile
				tson::Tile* invalidTile = tileData[{0, 4}]; // x:0,  y:4  - There is no tile here, so this will be nullptr.
																   // Be careful with this, as it expands the map with an ID of {0,4} pointing
																   // to a nullptr...

				//Individual tiles should be retrieved by calling the safe version:
				tson::Tile* safeInvalid = layer->getTileData(0, 5); //Another non-existent tile, but with safety check.
																		 //Will not expand the map with a nullptr

				tson::Tile* tile1 = layer->getTileData(4, 4);       //x:4,  y:4  - Points to tile with ID 1 (Tiled internal ID: 0)
				tson::Tile* tile2 = layer->getTileData(5, 4);       //x:5,  y:4  - Points to tile with ID 3 (Tiled internal ID: 2)
				tson::Tile* tile3 = layer->getTileData(8, 14);      //x:8,  y:14 - Points to tile with ID 2 (Tiled internal ID: 1)
				tson::Tile* tile4 = layer->getTileData(17, 5);      //x:17, y:5  - Points to tile with ID 5 (Tiled internal ID: 4)

				//New in v1.2.0
				//You can now get tiles with positions and drawing rect via tson::TileObject
				//Drawing rects are also accessible through tson::Tile.
				tson::TileObject* tileobj1 = layer->getTileObject(4, 4);
				tson::Vector2f position = tileobj1->getPosition();
				tson::Rect drawingRect = tileobj1->getDrawingRect();

				//You can of course also loop through every tile!
				for (const auto& [id, tile] : tileData)
				{
					//Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
					//Would be unnecessary otherwise.
					if (tile != nullptr)
						int tileId = tile->getId(); //A bit verbose, as this is the same as id from the key, but you get the idea.
				}
			}
		}

		//If an object supports properties, you can easily get a property value by calling get<T>() or the property itself with getProp()
		int myInt = layer->get<int>("my_int");
		float myFloat = layer->get<float>("my_float");
		bool myBool = layer->get<bool>("my_bool");
		std::string myString = layer->get<std::string>("my_string");
		tson::Colori myColor = layer->get<tson::Colori>("my_color");

		fs::path file = layer->get<fs::path>("my_file");

		tson::Property* prop = layer->getProp("my_property");
	}
	else //Error occured
	{
		LoggerProvider::log("Map loading error occured: " + map->getStatusMessage(), LogSeverity::Fatal, LogType::General);
		throw exception();
	}
*/