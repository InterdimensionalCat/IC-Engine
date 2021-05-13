//DrawableObject.h
#pragma once
#include "SFML/Graphics.hpp"

namespace ic::gfx {

    class Renderer;
    /**
     * @brief                         DrawableObject is the superclass that represents a textured object drawable by the engine
    */
    class DrawableObject : public sf::Transformable {
    public:

        friend class Renderer;

        /*
        * sets the origin to be the center of the objects bounding box by default
        */
        DrawableObject(const std::string& texture);

        /*
        * 
        */
        virtual ~DrawableObject();
     
        /**
         * @brief                     Updates the origin of the object
         * @param origin              The new origin of the object
        */
        void updateOrigin(const sf::Vector2f& origin);

        /**
         * @brief                     Updates the position of the object
         * @param position            Thew new position
        */
        void updatePosition(const sf::Vector2f& position);

        /**
         * @brief                     Updates the rotation of the object
         * @param rotation            The new rotation
        */
        void updateRotation(const float rotation);

        /**
         * @brief                     Updates the scale of the object
         * @param scalefactors        The new scale
        */
        void updateScale(const sf::Vector2f& scalefactors);

        /**
         * @brief                     The function that actually draws the object,  should call SFML's internal draw function when implimented
         * @param renderer            The engine renderer
         * @param states              The current states for the DrawableTree, this will differ for each DrawableTree node so it cannot
         *                            just be passed through the renderer
         * 
         * @TODO                      Make this pure virtual, no reason not to
        */
        virtual void draw(Renderer& renderer, sf::RenderStates states) {}

        /**
         * @brief                     Previous origin, for linear interpolation purposes
        */
        sf::Vector2f prevOrigin;

        /**
         * @brief                    Previous position, for linear interpolation purposes
        */
        sf::Vector2f prevPosition;

        /**
         * @brief                    Previous rotation, for linear interpolation purposes
        */
        float prevRotation;

        /**
         * @brief                    Previous scale, for linear interpolation purposes
        */
        sf::Vector2f prevScale;

        /**
         * @brief                    file name of the texture this DrawableObject uses
        */
        std::string texturename;
    };


}