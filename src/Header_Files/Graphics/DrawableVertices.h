#pragma once
#include "DrawableObject.h"

namespace ic::gfx {

    class Renderer;

    /**
     * @brief                         Primative drawable type that can be used to create
     *                                many different 2D textured drawable objects, still has
     *                                only one transform for the whole object, so large composite
     *                                drawables is impossible
    */
    class DrawableVertices : public DrawableObject {
    public:

        /**
         * @brief                     Constructs a DrawableVertices object with the given texture, vertices,
         *                            and primative type
         * @param texture             Name of the texture associated with this drawable
         * @param vertices_0_to_1     The vertices to be textured, vertex ranges from 0 to 1, and the actual size
         *                            is a function of this and the scale of the object
         * @param type                The sfml primative type of the object, more on primative types here and vetex arrays here:
         *                            https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
        */
        DrawableVertices(const std::string& texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type);
        ~DrawableVertices();

        /**
         * @brief                     Updates the internal vertex array with the supplied new vertices
         * @param vertices_0_to_1     The vertices to update with, vertex ranges from 0 to 1, and the actual size
         *                            is a function of this and the scale of the object
        */
        void update(const std::vector<sf::Vertex>& vertices_0_to_1);

        /**
         * @brief                     Draws the object, calls the internal SFML draw call for vertex arrays
         * @param renderer            The renderer supplied to do the actual drawing
         * @param states              The current renderstates at the DrawableObjectTree node that contains this object
        */
        void draw(Renderer& renderer, sf::RenderStates states) override;

    private:

        //sf::Vector2f prevOrigin;
        //sf::Vector2f prevPosition;
        //float prevRotation;
        //sf::Vector2f prevScale;

        /**
         * @brief                     The vertex array that SFML uses to draw this primative, more on using vertex arrays
         *                            here: https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
        */
        sf::VertexArray array;

        //std::string texturename;
    };
}
