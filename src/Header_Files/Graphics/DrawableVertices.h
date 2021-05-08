#pragma once
#include "DrawableObject.h"

namespace ic::gfx {

    class Renderer;

    //textured, transformable, drawable object
    class DrawableVertices : public DrawableObject {
    public:
        DrawableVertices(const std::string& texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type);
        ~DrawableVertices();

        void update(const std::vector<sf::Vertex>& vertices_0_to_1);
        void draw(Renderer& renderer, sf::RenderStates states) override;

    private:
        sf::Vector2f prevOrigin;
        sf::Vector2f prevPosition;
        float prevRotation;
        sf::Vector2f prevScale;

        sf::VertexArray array;
        std::string texturename;
    };
}
