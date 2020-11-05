#pragma once
#include "State.h"
#include "Button.h"
#include <array>
#include "MenuButton.h"

class MenuState :
	public State
{
public:
	MenuState(std::shared_ptr<StateManager> p);
	virtual ~MenuState() {}
	virtual void init();
	virtual void enter();
	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);
	virtual void exit();
	virtual string getName() const { return "MENU"; };

	void select(std::string pressedButtonName);
private:
	Text title;
	std::array<std::shared_ptr<MenuButton>, 3> buttons;

	//careful, font needs to be active 
	//for the entire duration of the text it
	//is being used for
	Font titleFont;
};

