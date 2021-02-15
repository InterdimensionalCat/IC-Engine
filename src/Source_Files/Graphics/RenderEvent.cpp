//#include "RenderEvent.h"
#include "Renderer.h"
#include "DrawableObject.h"


using namespace ic::gfx;

	//LoadTextureEvent::LoadTextureEvent(const std::string& textureName) : textureName(textureName) {

	//}

	//void LoadTextureEvent::excecute(Renderer& renderer) const {
	//	if (renderer.textures.find(textureName) != renderer.textures.end()) {
	//		return;
	//	}
	//	renderer.textures.emplace(textureName, std::make_unique<ic::Texture>(textureName));
	//}


	//UnloadTextureEvent::UnloadTextureEvent(const std::string& textureName) : textureName(textureName) {
	//
	//}

	//void UnloadTextureEvent::excecute(Renderer& renderer) const {
	//	renderer.textures.erase(textureName);
	//}

	//CreateDrawableEvent::CreateDrawableEvent(const std::string texture, const std::vector<sf::Vertex>& vertices_0_to_1, const sf::PrimitiveType type) : texture(texture), vertices_0_to_1(vertices_0_to_1), type(type) {

	//}

	//void CreateDrawableEvent::excecute(Renderer& renderer) const {
	//	renderer.drawables.push_back(std::make_unique<DrawableObject>(texture, vertices_0_to_1, type));
	//}