#pragma once
#include <unordered_map>
#include <map>

//InputHandle.h
/*
 object that manages all input to the program through keyboard/mouse/gamepad(eventually)
 and distributes events to the eventlisteners
*/

namespace ic {

	class InputHandle
	{
	public:
		InputHandle() {}
		~InputHandle() {}

		//TODO: create methods to check for these with a particular window
		//only parse input is the window has focus

		//determine if a key is held down
		//bool isDown(sf::Keyboard::Key key) const;

		//determine if a mouse button is held down
		//bool isDown(sf::Mouse::Button key) const;

		//determine if a key was pressed on this update
		//bool isPressed(sf::Keyboard::Key key) const;

		//determine if a mouse button was pressed on this update
		//bool isPressed(sf::Mouse::Button key) const;

		//read in all input given on this frame
		//bool updateInput(const float dt, sf::RenderWindow* window);

		//add and remove input event listeners
		//void addListener(EventListener* new_listener);
		//void removeListener(EventListener* to_remove);

		//map containing all the keys
		//std::unordered_map<int, sf::Keyboard::Key > pressedKeys;
		//std::unordered_map<int, sf::Mouse::Button> pressedButtons;

		//std::vector<EventListener*> listeners;

		//if window is "inactive" for whatever reason, do not
		//register inputs/poll certain events
		//bool active = true;

	};
}