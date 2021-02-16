#pragma once
#include <string>
#include <memory>

namespace ic::gfx {

	class DrawableObject;
	class Renderer;
	class RenderComponent;

	struct RenderEvent {
		RenderEvent() {}
		virtual ~RenderEvent() {}
		virtual void excecute(Renderer& renderer) const = 0;

		//void (*exceuctionFunction)(Renderer&);
	};


	struct LoadTextureEvent :  RenderEvent {
		LoadTextureEvent(const std::string& textureName);
		void excecute(Renderer& renderer) const override;
		std::string textureName;
	};

	struct UnloadTextureEvent : RenderEvent {
		UnloadTextureEvent(const std::string& textureName);
		void excecute(Renderer& renderer) const override;
		std::string textureName;
	};

	void createDrawableTree(std::unique_ptr<DrawableObject> baseDrawable);
	void createDrawableObjectFront(std::unique_ptr<DrawableObject> drawable, std::shared_ptr<DrawableObjTree> parent);
	void createDrawableObjectBack(std::unique_ptr<DrawableObject> drawable, std::shared_ptr<DrawableObjTree> parent);

	struct CreateDrawableEvent : RenderEvent {
		CreateDrawableEvent(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type);
		void excecute(Renderer& renderer) const override;
		std::string texturename;
		std::vector<sf::Vertex> vertices_0_to_1;
		sf::PrimitiveType type;
	};
}
