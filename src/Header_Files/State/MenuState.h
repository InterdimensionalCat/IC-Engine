#pragma once
#include "State.h"
#include "Button.h"

class MenuState :
	public State
{
public:
	MenuState(StateManager* p);
	virtual ~MenuState() {}
	virtual void init();
	virtual void enter() {};
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	virtual void exit() {};
	virtual string getName() const { return "MENU"; };

	void select();
private:
	Button title;
	vector<Button> options;
	int currentSelection;
	int clickDelay = 0;
};

