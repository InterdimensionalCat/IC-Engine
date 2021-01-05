#include "DrawableObject.h"
#include "SFML\Graphics.hpp"
#include "Renderer.h"
#include "ActorUID"

using namespace ic;

DrawableObject::DrawableObject(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type, const ActorUID& id) : id(id) {
    array.setPrimitiveType(type);
    update(vertices_0_to_1);

    Transformable::setOrigin(sf::Vector2f(0.5, 0.5));

    prevOrigin = Transformable::getOrigin();
    prevPosition = Transformable::getPosition();
    prevRotation = Transformable::getRotation();
    prevScale = Transformable::getScale();
}

DrawableObject::~DrawableObject() {

}

void DrawableObject::update(const std::vector<sf::Vertex>& vertices_0_to_1) {
    auto size = vertices_0_to_1.size();
    array.resize(size);
    for (int i = 0; i < size; i++) {
        array[i] = vertices_0_to_1.at(i);
    }
}

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

void DrawableObject::draw(Renderer& renderer, sf::RenderStates states) {
    auto tex = renderer.textures.find(texturename);
    states.transform *= Transformable::getTransform();
    for (auto& obj : backchildren) {
        obj->draw(renderer, states);
    }
    if (tex != renderer.textures.end()) {
        states.texture = tex->second->getTexturePtr();
        renderer.window->draw(array, states);
    }
    for (auto& obj : frontchildren) {
        obj->draw(renderer, states);
    }
}