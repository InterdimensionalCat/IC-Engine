#include "Level.h"
#include "Scene.h"
#include "ActorPool.h"
#include "tilemap.h"
#include "SceneView.h"
#include "ComponentManager.h"
#include "Components.h"
#include "Camera.h"
#include "Parallax.h"
#include "StdoutRedirect.h"
#include "Renderer.h"
#include "Window.h"

using namespace ic;

Level::Level(Scene* scene) : scene(scene) {
	tilemap = std::make_shared<Tilemap>();
	loadLevel("newLevel_1-px");
}

void Level::update() {
	camera->updateWindow(*Renderer::get()->window);
	parallaxEngine->move(*camera);
}

void Level::draw(const float interpol) {
	parallaxEngine->draw(*Renderer::get()->window);
	tilemap->draw(*Renderer::get()->window);
}

void Level::loadLevel(const std::string& levelname) {

	scene->actorPool->actors.clear();
	scene->actorPool->freeActors.clear();
	scene->compManager->componentPools.clear();

	currentlevelname = levelname;
	std::filesystem::path mappath(std::filesystem::current_path());
	mappath /= "resources";
	mappath /= "maps";
	mappath /= levelname;
	mappath += ".tmx";

	float widthPixels = 0;
	float heightPixels = 0;
	tmx::Map map;


	StdoutRedirect::redirectCout();
	bool loaded = false;

	try {
		loaded = map.load(mappath.string());
		if (!loaded) {
			throw std::exception();
		}
	}
	catch (std::exception e) {
		Logger::error("TMX map with name {}.tmx  at path {} failed to load!",
			levelname, mappath.string());
	}

	StdoutRedirect::restoreCout();

	if (loaded) {


		widthPixels = (float)(s2d::toPixels((float)map.getLayers().at(0)->getSize().x));
		heightPixels = (float)(s2d::toPixels((float)map.getLayers().at(0)->getSize().y));

		Level::mapwidth = s2d::toMeters(widthPixels);
		Level::mapheight = s2d::toMeters(heightPixels);

		for (auto& layer : map.getLayers())
		{
			if (layer->getType() == tmx::Layer::Type::Object) {

				auto& objlayer = layer->getLayerAs<tmx::ObjectGroup>();
				for (auto& obj : objlayer.getObjects()) {
					auto actorname = obj.getName();

					auto variantNameItr = std::find_if(obj.getProperties().begin(), obj.getProperties().end(), [](const tmx::Property val) {
						return val.getName() == "VariantName";
						});
					std::string variantname = "";
					if (variantNameItr != obj.getProperties().end()) {
						variantname = variantNameItr->getStringValue();
					}


					scene->actorPool->spawnActor(actorname, variantname, obj);

				}
			}

			if (layer->getType() == tmx::Layer::Type::Tile) {
				auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				auto tiles = tileLayer.getTiles();
				auto firstTileNum = tiles.at(0).ID;

				std::string tilesetname;
				for (auto& property : tileLayer.getProperties()) {
					if (property.getName() == "tilesetname") {
						tilesetname = property.getStringValue();
						break;
					}
				}

				for (size_t i = 0; i < map.getTilesets().size(); i++) {
					auto set = map.getTilesets().at(i);

					if (set.getName() == tilesetname) {
						tilemap->loadMap(s2d::toMeters(widthPixels), s2d::toMeters(heightPixels), tiles, set, tilesetname);
						continue;
					}
				}
			}
		}
	}

	for (auto entry : SceneView<PlayerFlag>(scene)) {
		camera = std::make_shared<Camera>(widthPixels, heightPixels, entry, scene);
	}

	std::string parallaxname;
	float baseX;
	float baseY;
	float growthX;
	float growthY;

	for (auto& property : map.getProperties()) {
		if (property.getName() == "BackgroundName") {
			parallaxname = property.getStringValue();
		}

		if (property.getName() == "baseParallaxX") {
			baseX = property.getFloatValue();
		}

		if (property.getName() == "baseParallaxY") {
			baseY = property.getFloatValue();
		}

		if (property.getName() == "growthParallaxX") {
			growthX = property.getFloatValue();
		}

		if (property.getName() == "growthParallaxY") {
			growthY = property.getFloatValue();
		}
	}


	parallaxEngine = std::make_shared<Parallax>(parallaxname, baseX, baseY, growthX, growthY);
}