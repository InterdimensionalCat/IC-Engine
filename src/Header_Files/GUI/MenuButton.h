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

    MenuButton(const s2d::Point& center, const std::string& text, const std::string& font, const size_t& fontSize, MenuState* parent);

    //selection functions
    virtual void onSelectEnd();
    virtual void onSelectStart();

    //state functions
    virtual void unhovered();
    virtual void hovered();
    virtual void selected();

    //update functions
    virtual void draw(Renderer* renderer);
    virtual void updateListener(const float dt);

    MenuState* parent;
    sf::Text option;
    sf::Font buttonFont;
};
