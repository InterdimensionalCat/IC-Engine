#include "DrawableVertices.h"
#include "Renderer.h"

using namespace ic::gfx;


DrawableVertices::DrawableVertices(const std::string& texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type) : DrawableObject(texture) {
    array.setPrimitiveType(type);
    update(vertices_0_to_1);
}

DrawableVertices::~DrawableVertices() {

}

void DrawableVertices::update(const std::vector<sf::Vertex>& vertices_0_to_1) {
    auto size = vertices_0_to_1.size();
    array.resize(size);
    for (int i = 0; i < size; i++) {
        array[i] = vertices_0_to_1.at(i);
    }
}

void DrawableVertices::draw(Renderer& renderer, sf::RenderStates states) {
    states.transform *= Transformable::getTransform();
    if (texturename != "") {
        states.texture = renderer.getTexture(texturename)->getTexturePtr();
    }
    renderer.getWindow()->draw(array, states);
}