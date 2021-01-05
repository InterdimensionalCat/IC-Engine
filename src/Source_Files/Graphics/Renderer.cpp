#include "include.h"
#include "Renderer.h"
#include "RenderEvent.h"
#include "RenderComponent.h"

using namespace ic;

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

void Renderer::updateInput() {


	//poll an event
	sf::Event event;
	while (window->pollEvent(event))
	{

		if (event.type == sf::Event::Closed) {

		}

		if (event.type == sf::Event::KeyPressed) {

		}

		if (event.type == sf::Event::MouseButtonPressed) {

		}
	}
}

void Renderer::preRender(const float interpol) {
	updateRenderComponents();
	handleEvents();
	Renderer::interpol = interpol;
	window->clear(sf::Color(255, 255, 255, 255));
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
		//event->excecute(*this);
		event->exceuctionFunction(*this);
	}
}

void Renderer::updateRenderComponents() {
	for (auto& c : components) {
		c->update(this);
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
