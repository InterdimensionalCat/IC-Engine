//Button.h
/*
  Abstract button GUI class, used to make more specific
  purpose GUI buttons
*/
#pragma once
#include "Widget.h"
#include "Space2D.h"

class Button :
    public Widget
{


public:
    Button(const s2d::ScreenUnits::Rectangle& bounds, const float bordersize, const Color& interior_color, const Color& border_color);

    //Event handling functions
    virtual void handleEvent(const sf::Event& e, Window& window);
    void onMouseMove(const sf::Event& e);
    void onMousePress(const sf::Event& e);
    void onMouseRelease(const sf::Event& e);
    void onKeyPress(const sf::Event& e);
    void onKeyRelease(const sf::Event& e);

    //selection functions
    virtual void onSelectEnd() = 0;
    virtual void onSelectStart() = 0;

    //state functions
    virtual void unhovered();
    virtual void hovered();
    virtual void selected();

    //update functions
    virtual void draw(Renderer* renderer);
    virtual void updateListener(const float dt) = 0;

    enum class ButtonState {
        Unhovered = 0,
        Hovered = 1,
        Selected = 2
    };

    ButtonState state = ButtonState::Unhovered;
};

