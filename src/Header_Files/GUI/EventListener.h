#pragma once
//EventListener.h
/*
  Interface for defining input event listeners (such as GUI elements)
  Every window event that the game window intercepts each frame gets sent
  to the event listeners for individual handling
*/
class EventListener {
public:

	//called when an event occurs and handles the event
	virtual void handleEvent(const sf::Event& e, Window& window) = 0;

	//called every input update before any events are handled
	virtual void updateListener(const float dt) = 0;

	bool active = true;
};