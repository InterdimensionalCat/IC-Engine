#pragma once
#include <unordered_map>
#include <map>

//InputHandle.h
/*
 object that manages all input to the program through keyboard/mouse/gamepad(eventually)
 and distributes events to the eventlisteners
*/

class Game;
class EventListener;

class InputHandle
{
public:
	InputHandle(Game* in) : instance(in) {}
	~InputHandle() {}

	//TODO: create methods to check for these with a particular window
	//only parse input is the window has focus

	//determine if a key is held down
	bool isDown(Keyboard::Key key) const;

	//determine if a mouse button is held down
	bool isDown(Mouse::Button key) const;

	//determine if a key was pressed on this update
	bool isPressed(Keyboard::Key key) const;

	//determine if a mouse button was pressed on this update
	bool isPressed(Mouse::Button key) const;

	//read in all input given on this frame
	void updateInput(const float dt);

	//add and remove input event listeners
	void addListener(EventListener* new_listener);
	void removeListener(EventListener* to_remove);

	RenderWindow* getWindow();

	//map containing all the keys
	unordered_map<int, Keyboard::Key> pressedKeys;
	unordered_map<int, Mouse::Button> pressedButtons;

	std::vector<EventListener*> listeners;

	Game* instance;

	//if window is "inactive" for whatever reason, do not
	//register inputs/poll certain events
	bool active = true;

};