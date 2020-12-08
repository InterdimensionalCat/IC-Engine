#include "include.h"
#include <unordered_map>
#include <map>
#include "GameEngine2020.h"
#include "InputHandle.h"
#include "EventListener.h"
#include "SettingsProvider.h"

bool InputHandle::updateInput(const float dt, sf::RenderWindow* window) {

	//clear pressed keys from the previous update
	pressedKeys.clear();
	pressedButtons.clear();

	auto MainWindow = window;

	active = MainWindow->hasFocus();
	//active = true;

	//update each listener before polling
	for (auto& l : listeners) {
		if (l->active) {
			l->updateListener(dt);
		}
	}

	//poll an event

	//window events for main window;

	sf::Event event;
	while (MainWindow->pollEvent(event))
	{

		//events that should be polled regardless of window active state:
		if (event.type == sf::Event::Closed) {
			return false;
		}

		if (active) {
			//events that should only be polled when the window is active:

			for (auto& l : listeners) {
				if (l->active) {
					l->handleEvent(event, *MainWindow);
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				pressedKeys[(int)event.key.code] = event.key.code;

				if (event.key.code == sf::Keyboard::I) {
					std::cout << "In game debug mode toggled\n";
					SettingsProvider::setSetting<bool>("debug", !SettingsProvider::getSetting<bool>("debug"));
					//instance->debug = !instance->debug;
				}

				if (event.key.code == sf::Keyboard::Escape) {
					return false;
				}

			}

			if (event.type == sf::Event::MouseButtonPressed) {
				pressedButtons[(int)event.mouseButton.button] = event.mouseButton.button;
			}

		}
	}

	return true;
}

bool InputHandle::isDown(sf::Keyboard::Key key) const {
	return sf::Keyboard::isKeyPressed(key);
}

bool InputHandle::isDown(sf::Mouse::Button key) const {
	return sf::Mouse::isButtonPressed(key);
}

bool InputHandle::isPressed(sf::Keyboard::Key key) const {
	return pressedKeys.find((int)key) != pressedKeys.end();
}

bool InputHandle::isPressed(sf::Mouse::Button key) const {
	return pressedButtons.find((int)key) != pressedButtons.end();
}

void InputHandle::addListener(EventListener* new_listener) {
	listeners.push_back(new_listener);
}

void InputHandle::removeListener(EventListener* to_remove) {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), to_remove), listeners.end());
}