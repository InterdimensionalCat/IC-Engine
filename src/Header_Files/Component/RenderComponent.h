#pragma once
#include "Component.h"


//enum sf::PrimitiveType;
//class sf::Vertex;
//class std::string;

namespace ic {
	namespace gfx {
		class Renderer;
	}
	

	class RenderComponent : public Component {
	public:
		RenderComponent(const ActorData& dat) : Component(dat) {}
		virtual ~RenderComponent() {}
		virtual void start(ic::gfx::Renderer& renderer) = 0;
		virtual void update(ic::gfx::Renderer & renderer) = 0;

		//idea: have a subclass sandbox of primative drawing functions in rendercomponent, then use the data file to make calls to these methods with given paramaters (psudo-interpreter method)


		//void loadTexture(const std::string& texturename, ic::gfx::Renderer& renderer);
		//void unloadTexture(const std::stringbuf& texturename, ic::gfx::Renderer& renderer);
		//void addBackChild(ActorUID parentID, ActorUID childID, ic::gfx::Renderer& renderer);
		//void addFrontChild(ActorUID parentID, ActorUID childID, ic::gfx::Renderer& renderer);
		//void removeChild(ActorUID childID, ic::gfx::Renderer& renderer);

		//createDrawableVertices(const std::string& texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type, ic::gfx::Renderer& renderer);
	};
}