#include "include.h"
#include "Button.h"

using namespace s2d;

Button::Button(const Rectangle& bounds, const float bordersize, const Color& interior_color, const Color& border_color) : Widget(bounds, bordersize, interior_color, border_color) {

}

void Button::handleEvent(const sf::Event& e, Window& window) {
    switch (e.type) {
    case Event::MouseButtonReleased:
        onMouseRelease(e);
        break;
    case Event::MouseButtonPressed:
        onMousePress(e);
        break;
    case Event::MouseMoved:
        onMouseMove(e);
        break;
    case Event::KeyPressed:
        onKeyPress(e);
        break;
    case Event::KeyReleased:
        onKeyRelease(e);
        break;
    default:
        break;
    }
}

void Button::onKeyPress(const sf::Event& e) {
    if (e.key.code == sf::Keyboard::Enter && this->state == ButtonState::Hovered) {
        selected();
        onSelectStart();
    }
}

void Button::onKeyRelease(const sf::Event& e) {
    if (e.key.code == sf::Keyboard::Enter && this->state == ButtonState::Hovered) {
        unhovered();
        onSelectEnd();
    }
}

void Button::onMouseMove(const sf::Event& e) {
    Point local_mouse_pos = Point((float)e.mouseMove.x, (float)e.mouseMove.y);
    if (this->bounds.contains(local_mouse_pos)) {
        if (state == ButtonState::Unhovered) {
            hovered();
        }
    }
    else {

        if (state == ButtonState::Hovered) {
            unhovered();
        }
    }

    if (state == ButtonState::Selected) {
        //move mouse wheel while selected?
    }
}

void Button::onMousePress(const sf::Event& e) {
    if (e.mouseButton.button != Mouse::Left) return;
    Point local_mouse_pos = Point((float)e.mouseButton.x, (float)e.mouseButton.y);
    if (this->bounds.contains(local_mouse_pos)) {
        selected();
        onSelectStart();
    }
}

void Button::onMouseRelease(const sf::Event& e) {
    if (e.mouseButton.button != Mouse::Left || state != ButtonState::Selected) return;
    Point local_mouse_pos = Point((float)e.mouseButton.x, (float)e.mouseButton.y);

    onSelectEnd();

    if (this->bounds.contains(local_mouse_pos)) {
        hovered();
    }
    else {
        unhovered();
    }
}


void Button::unhovered() {
    state = ButtonState::Unhovered;
}

void Button::hovered() {
    state = ButtonState::Hovered;
}

void Button::selected() {
    state = ButtonState::Selected;
}

void Button::draw(std::shared_ptr<Renderer>& renderer) {
    Widget::draw(renderer);
}