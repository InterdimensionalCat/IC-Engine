//MenuButton.h
/*
  Implementation of the button interface for main menu buttons
*/
#pragma once
#include "Button.h"
#include <memory>

class MenuState;

class MenuButton :
    public Button
{
public:

    MenuButton(const s2d::Point& center, const string& text, const string& font, const size_t& fontSize, std::shared_ptr<MenuState>& parent);

    //selection functions
    virtual void onSelectEnd();
    virtual void onSelectStart();

    //state functions
    virtual void unhovered();
    virtual void hovered();
    virtual void selected();

    //update functions
    virtual void draw(std::shared_ptr<Renderer>& renderer);
    virtual void updateListener(const float dt);

    std::shared_ptr<MenuState> parent;
    Text option;
    Font buttonFont;
};
