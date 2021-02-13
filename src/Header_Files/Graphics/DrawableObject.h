#pragma once
#include "SFML/Graphics.hpp"

namespace ic {
	//class DrawableObject : public sf::Drawable, public sf::Transformable {
	//public:
	//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	//};

	//class DrawableSprite : public DrawableObject {
 //       DrawableSprite() {}
 //       DrawableSprite(const sf::Texture texture) : sprite(sf::Sprite(texture)) {}
 //       DrawableSprite(const sf::Texture texture, const sf::IntRect& rectangle) : sprite(sf::Sprite(texture, rectangle)) {}
 //       void setTexture(const sf::Texture texture) {
 //           sprite.setTexture(texture);
 //       }
 //       void setTextureRect(const sf::IntRect& rectangle) {
 //           sprite.setTextureRect(rectangle);
 //       }
 //       //void setColor(const sf::Color& color);
 //       //const sf::Texture* getTexture() const;
 //       //const sf::IntRect& getTextureRect() const;
 //       //const sf::Color& getColor() const;
 //       //sf::FloatRect getLocalBounds() const;
 //       //sf::FloatRect getGlobalBounds() const;
 //       void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
 //           target.draw(sprite);
 //       }
 //   private:
 //       sf::Sprite sprite;
	//};

    class Renderer;
    class ActorUID;


    //textured, transformable, drawable object
    class DrawableObject : public sf::Drawable, public sf::Transformable {
    public:
        DrawableObject(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type, const ActorUID& id);
        ~DrawableObject();
        //void update(const std::vector<sf::Vertex>& vertices_0_to_1);
        void updateOrigin(const sf::Vector2f& origin);
        void updatePosition(const sf::Vector2f& position);
        void updateRotation(const float rotation);
        void updateScale(const sf::Vector2f& scalefactors);
        void draw(Renderer& renderer, sf::RenderStates states);

        sf::Vector2f prevOrigin;
        sf::Vector2f prevPosition;
        float prevRotation;
        sf::Vector2f prevScale;

        //sf::VertexArray array;
        std::string texturename;
    };
}