#include "include.h"
#include <unordered_map>
#include <map>
#include "GameEngine2020.h"
#include "InputHandle.h"

void InputHandle::updateInput(const float dt) {

	//clear pressed keys from the previous update
	pressedKeys.clear();
	pressedButtons.clear();

	auto MainWindow = getWindow();

	//active = MainWindow->hasFocus();
	active = true;

	//update each listener before polling
	for (auto& l : listeners) {
		if (l->active) {
			l->updateListener(dt);
		}
	}

	//poll an event

	//window events for main window;

	Event event;
	while (MainWindow->pollEvent(event))
	{

		//events that should be polled regardless of window active state:
		if (event.type == Event::Closed) {
			instance->stop();
		}

		if (active) {
			//events that should only be polled when the window is active:

			for (auto& l : listeners) {
				if (l->active) {
					l->handleEvent(event, *MainWindow);
				}
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

RenderWindow* InputHandle::getWindow() {
	return instance->renderer->window.get();
}

void InputHandle::addListener(shared_ptr<EventListener> new_listener) {
	listeners.push_back(new_listener);
}

void InputHandle::removeListener(shared_ptr<EventListener> to_remove) {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), to_remove), listeners.end());
}