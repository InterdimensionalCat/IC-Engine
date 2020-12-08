#pragma once
#include "State.h"
#include "Button.h"
#include <array>
#include "MenuButton.h"
//MenuState.h
/*
  State that contains the logic and objects for the Main menu that displays
  as soon as the program is started
*/

class MenuState :
	public State
{
public:
	MenuState(StateManager* p);
	virtual ~MenuState() {}
	virtual void init();
	virtual void enter();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	virtual void exit();
	virtual std::string getName() const { return "MENU"; };

	void select(std::string pressedButtonName);
private:
	sf::Text title;
	std::array<std::unique_ptr<MenuButton>, 3> buttons;

	//careful, font needs to be active 
	//for the entire duration of the text it
	//is being used for
	sf::Font titleFont;
};

