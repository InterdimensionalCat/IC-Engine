#include "include.h"
#include "Window.h"
#include "WindowEventListener.h"
#include "Input.h"
#include "imgui-SFML.h"
#include "ImGui/imgui.h"
#include "InputEventBus.h"
#include "InputEvent.h"

//Scene -> Layers (hard coded tilemap layer, hardcoded GUI layer)



using namespace ic;

Window::Window() {

	//creates an SFML window using the width, height, and name specified in the game Settings
	window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(Settings::getWidth(), Settings::getHeight()),
		Settings::getTitle()
		);

	if (Settings::getVsync()) {
		window->setVerticalSyncEnabled(true);
		Logger::info("Vsync enabled.");
	}
	else {
		window->setFramerateLimit((unsigned int)Settings::getTargetFPS());
		Logger::info("Vsync not enabled, fps set to {:03.1f}", Settings::getTargetFPS());
	}

	//causes keypresses to only send one window event
	window->setKeyRepeatEnabled(false);

	//registerWindowEventListener(KeyboardGlobal::listener);

	//ImGui::SFML::Init(*window);
	//guiClock.restart();

}

Window::~Window() {
	//for (auto& listener : listeners) {
	//	listener.reset();
	//}
	//while (!listeners.empty()) {
	//	listeners.pop_back();
	//}
	//listeners.clear();
	window->close();
	//ImGui::SFML::Shutdown();
}

bool Window::pollEvents() {


	//poll an event


	//for (auto& listener : listeners) {
	//	listener->update(*this);
	//}
	sf::Event event;
	while (window->pollEvent(event))
	{

		//ImGui::SFML::ProcessEvent(*window, event);

		//for (auto& listener : listeners) {
		//	if (listener->handleWindowEvent(event)) {
		//		continue;
		//	}
		//}

		if (event.type == sf::Event::Closed) {
			//Settings::setSetting<bool>("running", false);
			return false;
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				//Settings::setSetting<bool>("running", false);
				return false;
			}

			if (event.key.code == sf::Keyboard::I) {
				Settings::setDebug(!Settings::getDebug());
				std::string debugswitch = Settings::getDebug() ? 
					"enabled" : "disabled";
				Logger::info("Debug Mode {}", debugswitch);
			}
		}

		switch (event.type) {
		case sf::Event::KeyPressed:
			InputEventBus::get()->publish(
				KeyboardPressKeyEvent(event.key.code)
			);
			break;
		case sf::Event::KeyReleased:
			InputEventBus::get()->publish(
				KeyboardReleaseKeyEvent(event.key.code)
			);
			break;
		default:
			break;
		}

	}

	return true;
}

void Window::clear() {
	window->clear(sf::Color(0, 0, 0, 255));
}

void Window::display() {
	window->display();
}

//bool Window::updateInput() {
//
//
//	//poll an event
//
//
//	for (auto& listener : listeners) {
//		listener->update(*this);
//	}
//	sf::Event event;
//	while (window->pollEvent(event))
//	{
//
//		//ImGui::SFML::ProcessEvent(*window, event);
//
//		for (auto& listener : listeners) {
//			if (listener->handleWindowEvent(event)) {
//				continue;
//			}
//		}
//
//		if (event.type == sf::Event::Closed) {
//			//Settings::setSetting<bool>("running", false);
//			return false;
//		}
//
//		if (event.type == sf::Event::KeyPressed) {
//			if (event.key.code == sf::Keyboard::Escape) {
//				//Settings::setSetting<bool>("running", false);
//				return false;
//			}
//
//			if (event.key.code == sf::Keyboard::I) {
//				Settings::setDebug(!Settings::getDebug());
//				std::string debugswitch = Settings::getDebug() ? 
//					"enabled" : "disabled";
//				Logger::info("Debug Mode {}", debugswitch);
//			}
//		}
//
//	}
//
//	return true;
//}
//
//void Window::preRender(const float interpol) {
//	this->interpol = interpol;
//	window->clear(sf::Color(255, 255, 255, 255));
//	//ImGui::SFML::Update(*window, guiClock.restart());
//}
//
//void Window::renderGui() {
//	//ImGui::SFML::Render(*window);
//}
//
//
//void Window::postRender() {
//	window->display();
//}
//
//void Window::registerWindowEventListener(
//	std::shared_ptr<WindowEventListener> listener) {
//	Logger::debug("Window event listener {} registered", listener->getName());
//	listeners.push_back(listener);
//}
