#pragma once
#include "State.h"
#include "Button.h"
#include <array>
#include "MenuButton.h"

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
	virtual string getName() const { return "MENU"; };

	void select(std::string &pressedButtonName);
private:
	Text title;
	std::array<std::shared_ptr<MenuButton>, 3> buttons;

	//careful, font needs to be active 
	//for the entire duration of the text it
	//is being used for
	Font titleFont;
};

