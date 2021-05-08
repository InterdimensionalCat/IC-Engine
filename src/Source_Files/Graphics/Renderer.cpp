#include "include.h"
#include "Renderer.h"
#include "RenderEvent.h"
//#include "RenderComponent.h"
#include "DrawableObject.h"
#include "DrawableVertices.h"

using namespace ic::gfx;

Renderer::Renderer() {
		window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(SettingsProvider::getSetting<int>("Width"), SettingsProvider::getSetting<int>("Height")), 
		SettingsProvider::getSetting<std::string>("Title")
	);

	if (SettingsProvider::getSetting<bool>("vsync")) {
		//V-sync doesnt really play nice with animations and I find that SFML can be
		//somewhat stuttery and I cant tell if V-sync makes it better or worse
		window->setVerticalSyncEnabled(true);
#ifdef debug_mode
		LoggerProvider::log("V-Sync Enabled\n");
#endif
	}
	else {
		window->setFramerateLimit((unsigned int)SettingsProvider::getSetting<float>("targetFPS"));
#ifdef debug_mode
		LoggerProvider::log("V-Sync disabled; fps is " + std::to_string(SettingsProvider::getSetting<float>("targetFPS")) + "\n");
#endif
	}

	window->setKeyRepeatEnabled(false);
}

Renderer::~Renderer() {
	window->close();
}

//void Renderer::updateInput() {
//
//
//	//poll an event
//	sf::Event event;
//	while (window->pollEvent(event))
//	{
//
//		if (event.type == sf::Event::Closed) {
//
//		}
//
//		if (event.type == sf::Event::KeyPressed) {
//
//		}
//
//		if (event.type == sf::Event::MouseButtonPressed) {
//
//		}
//	}
//}

void Renderer::preRender(const float interpol) {
	//updateRenderComponents();
	handleEvents();
	Renderer::interpol = interpol;
	window->clear(sf::Color(255, 255, 255, 255));
}

void Renderer::render() {
	for (auto& tree : drawableTrees) {
		tree->draw(*this, states);
	}
}

void Renderer::postRender() {
	window->display();
}

void Renderer::addEvent(std::unique_ptr<RenderEvent> event) {
	renderEventQueue.push(std::move(event));
}

void Renderer::handleEvents() {
	std::unique_ptr<RenderEvent> event(nullptr);
	while (pollEvent(event)) {
		event->excecute(*this);
		//event->exceuctionFunction(*this);
	}
}


bool Renderer::pollEvent(std::unique_ptr<RenderEvent>& event) {
	if (renderEventQueue.size() == 0) {
		return false;
	}
	else {
		event.reset();
		event = std::move(renderEventQueue.front());
		renderEventQueue.pop();
		return true;
	}
}


void Renderer::loadTexture(const std::string& texturename) {
	textures.insert(std::pair<std::string, std::shared_ptr<Texture>>(texturename, std::move(std::make_shared<Texture>(texturename))));
}

void Renderer::unloadTexture(const std::string& texturename) {
	auto texFound = textures.find(texturename);
	if (texFound != textures.end()) {
		textures.erase(texFound);
	}
	else {
		LoggerProvider::logAndThrowLogicError(
			"texture unload target " + texturename + " is not loaded!\n", LogSeverity::Fatal, LogType::Rendering);
	}
}

Texture* Renderer::getTexture(const std::string& texturename) {
	auto tex = textures.find(texturename);
	if (tex != textures.end()) {
		return tex->second.get();
	}
	else {
		LoggerProvider::logAndThrowLogicError(
			"texture unload target " + texturename + " is not loaded!\n", LogSeverity::Fatal, LogType::Rendering);
		return nullptr;
	}
}

void Renderer::createDrawableTree(std::unique_ptr<DrawableObject> baseDrawable, const ic::ActorUID& actor) {
	if (actorToTreeMap.find(actor) != actorToTreeMap.end()) {
		drawableTrees.push_back(std::make_shared<DrawableObjTree>(std::move(baseDrawable), actor));
		actorToTreeMap.insert(std::pair(actor, drawableTrees.at(drawableTrees.size() - 1)));
	}
	else {
		LoggerProvider::logAndThrowLogicError(
			actor.toString() + " bound to more than one DrawableObjTree!\n", LogSeverity::Fatal, LogType::Rendering);
	}
}

void Renderer::addDrawableTreeChildFront(const ic::ActorUID parentID, const ic::ActorUID childID) {
	addDrawableTreeChild(parentID, childID, true);
}
void Renderer::addDrawableTreeChildBack(const ic::ActorUID parentID, const ic::ActorUID childID) {
	addDrawableTreeChild(parentID, childID, false);
}

void Renderer::addDrawableTreeChild(const ic::ActorUID parentID, const ic::ActorUID childID, bool front) {
	auto parentTree = actorToTreeMap.find(parentID);
	auto childTree = actorToTreeMap.find(childID);

	if (parentTree == actorToTreeMap.end()) {
		LoggerProvider::logAndThrowLogicError(
			parentID.toString() + " does not reference a DrawableObjectTree!\n", LogSeverity::Fatal, LogType::Rendering);
	}

	if (childTree == actorToTreeMap.end()) {
		LoggerProvider::logAndThrowLogicError(
			childID.toString() + " does not reference a DrawableObjectTree!\n", LogSeverity::Fatal, LogType::Rendering);
	}

	if (childTree->second->parent.has_value()) {
		removeDrawableTreeChild(childID);
	}

	drawableTrees.erase(std::remove(drawableTrees.begin(), drawableTrees.end(), childTree->second), drawableTrees.end());

	if (front) {
		parentTree->second->addFrontChild(childTree->second);
	}
	else {
		parentTree->second->addBackChild(childTree->second);
	}

}
void Renderer::removeDrawableTreeChild(const ic::ActorUID childID) {
	auto childTree = actorToTreeMap.find(childID);

	if (childTree == actorToTreeMap.end()) {
		LoggerProvider::logAndThrowLogicError(
			childID.toString() + " does not reference a DrawableObjectTree!\n", LogSeverity::Fatal, LogType::Rendering);
	}

	if (!childTree->second->parent.has_value()) {
		LoggerProvider::logAndThrowLogicError(
			childID.toString() + " does not have a parent Tree!\n", LogSeverity::Fatal, LogType::Rendering);
	}

	ic::ActorUID parentID = childTree->second->parent.value();

	auto parentTree = actorToTreeMap.find(parentID);

	if (parentTree == actorToTreeMap.end()) {
		LoggerProvider::logAndThrowLogicError(
			parentID.toString() + " does not reference a DrawableObjectTree!\n", LogSeverity::Fatal, LogType::Rendering);
	}

	parentTree->second->removeChild(childTree->second);
	drawableTrees.push_back(childTree->second);
}

sf::RenderWindow* Renderer::getWindow() {
	return window.get();
}