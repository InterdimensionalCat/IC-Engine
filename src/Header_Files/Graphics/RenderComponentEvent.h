#pragma once
#include <string>
#include <memory>

namespace ic {

	class DrawableObject;
	class Renderer;
	class RenderComponent;

	struct RenderComponentEvent {
		RenderComponentEvent() {}
		virtual ~RenderComponentEvent() {}
		virtual void excecute(DrawableObject& object) const = 0;

		//void (*exceuctionFunction)(Renderer&);
	};


	//struct LoadTextureEvent :  RenderEvent {
	//	LoadTextureEvent(const std::string& textureName);
	//	void excecute(Renderer& renderer) const override;
	//	std::string textureName;
	//};

	//struct UnloadTextureEvent : RenderEvent {
	//	UnloadTextureEvent(const std::string& textureName);
	//	void excecute(Renderer& renderer) const override;
	//	std::string textureName;
	//};

	//struct CreateDrawableEvent : RenderEvent {
	//	CreateDrawableEvent(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type);
	//	void excecute(Renderer& renderer) const override;
	//	std::string texturename;
	//	std::vector<sf::Vertex> vertices_0_to_1;
	//	sf::PrimitiveType type;
	//};
}
