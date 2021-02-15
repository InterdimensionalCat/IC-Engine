#include "include.h"
#include "Renderer.h"
//#include "RenderEvent.h"
//#include "RenderComponent.h"

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
	//handleEvents();
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

//void Renderer::addEvent(std::unique_ptr<RenderEvent> event) {
//	renderEventQueue.push(std::move(event));
//}
//
//void Renderer::handleEvents() {
//	std::unique_ptr<RenderEvent> event(nullptr);
//	while (pollEvent(event)) {
//		//event->excecute(*this);
//		event->exceuctionFunction(*this);
//	}
//}
//
//void Renderer::updateRenderComponents() {
//	for (auto& c : components) {
//		c->update(this);
//	}
//}
//
//bool Renderer::pollEvent(std::unique_ptr<RenderEvent>& event) {
//	if (renderEventQueue.size() == 0) {
//		return false;
//	}
//	else {
//		event.reset();
//		event = std::move(renderEventQueue.front());
//		renderEventQueue.pop();
//		return true;
//	}
//}


void Renderer::loadTexture(const std::string& texturename) {
	textures.insert(std::pair<std::string, std::unique_ptr<Texture>>(texturename, std::move(std::make_unique<Texture>(texturename))));
}

void Renderer::unloadTexture(const std::string& texturename) {
	auto texFound = textures.find(texturename);
	if (texFound != textures.end()) {
		textures.erase(texFound);
	}
	else {
		LoggerProvider::logAndThrowLogicError("texture unload target " + texturename + " is not loaded!\n", LogSeverity::Fatal, LogType::Rendering);
	}
}

Texture* Renderer::getTexture(const std::string& texturename) {
	auto tex = textures.find(texturename);
	if (tex != textures.end()) {
		return tex->second.get();
	}
	else {
		LoggerProvider::logAndThrowLogicError("texture unload target " + texturename + " is not loaded!\n", LogSeverity::Fatal, LogType::Rendering);
		return nullptr;
	}
}

void Renderer::createDrawableTree(std::unique_ptr<DrawableObject> baseDrawable) {

}

void Renderer::createDrawableVertices(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type) {

}

sf::RenderWindow* Renderer::getWindow() {
	return window.get();
}