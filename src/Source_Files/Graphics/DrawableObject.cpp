#include "DrawableObject.h"
#include "SFML\Graphics.hpp"
#include "Renderer.h"
#include "ActorUID.h"

using namespace ic::gfx;

DrawableObject::DrawableObject(const std::string texture) : texturename(texture) {}

DrawableObject::~DrawableObject() {}

void DrawableObject::updateOrigin(const sf::Vector2f& origin) {
    prevOrigin = Transformable::getOrigin();
    Transformable::setOrigin(origin);
}

void DrawableObject::updatePosition(const sf::Vector2f& position) {
    prevPosition = Transformable::getPosition();
    Transformable::setPosition(position);
}

void DrawableObject::updateRotation(const float rotation) {
    prevRotation = Transformable::getRotation();
    Transformable::setRotation(rotation);
}

void DrawableObject::updateScale(const sf::Vector2f& scalefactors) {
    prevScale = Transformable::getScale();
    Transformable::setScale(scalefactors);
}