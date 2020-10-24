#include "include.h"
#include <unordered_map>
#include <map>
#include "Game.h"
#include "InputHandle.h"

void InputHandle::updateInput() {

	//clear pressed keys from the previous update
	pressedKeys.clear();
	pressedButtons.clear();

	auto MainWindow = instance->MainWindow->get();

	//poll an event

	//window events for main window;

	Event event;
	while (MainWindow->pollEvent(event))
	{
		if (event.type == Event::Closed) {
			instance->stop();
		}

		if (event.type == Event::KeyPressed) {
			pressedKeys[(int)event.key.code] = event.key.code;

			if (event.key.code == Keyboard::I) {
				cout << "In game debug mode toggled\n";
				instance->debug = !instance->debug;
			}

			if (event.key.code == Keyboard::Escape) {
				instance->stop();
			}

		}

		if (event.type == Event::MouseButtonPressed) {
			pressedButtons[(int)event.mouseButton.button] = event.mouseButton.button;
		}
	}

	//window events for subwindow

	for (auto & par : instance->subwindows) {
		auto wind = par.second->get();

		while (wind->pollEvent(event)) {

			if (event.type == Event::Closed) {
				wind->close();
			}

			if (event.type == Event::KeyPressed) {
				pressedKeys[(int)event.key.code] = event.key.code;

				if (event.key.code == Keyboard::I) {
					cout << "In game debug mode toggled\n";
					instance->debug = !instance->debug;
				}

				if (event.key.code == Keyboard::Escape) {
					wind->close();
				}

			}

			if (event.type == Event::MouseButtonPressed) {
				pressedButtons[(int)event.mouseButton.button] = event.mouseButton.button;
			}
		}
	}
}

bool InputHandle::isDown(Keyboard::Key key) const {
	return Keyboard::isKeyPressed(key);
}

bool InputHandle::isDown(Mouse::Button key) const {
	return Mouse::isButtonPressed(key);
}

bool InputHandle::isPressed(Keyboard::Key key) const {
	return pressedKeys.find((int)key) != pressedKeys.end();
}

bool InputHandle::isPressed(Mouse::Button key) const {
	return pressedButtons.find((int)key) != pressedButtons.end();
}

WindowData* InputHandle::getWindowData() {
	return instance->MainWindow;
}

WindowData* InputHandle::getWindowData(const std::string &subwindowname) {
	if (instance->subwindows.find(subwindowname) != instance->subwindows.end()) {
		return instance->subwindows.at(subwindowname).get();
	}
	else {
		cout << "Window not found!\n";
		return instance->MainWindow;
	}
}