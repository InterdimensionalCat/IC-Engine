#pragma once
#include <vector>
#include <memory>
#include "DrawableObject.h" 


//each actor that can be drawn has 1 and only 1 DrawableObjectTree, 
//if an actor wants multiple drawable objects, it must use the CompositeDrawableObject as its DrawableObject
namespace ic::gfx {
	class DrawableObjTree {
	public:
		DrawableObjTree(std::unique_ptr<DrawableObject> drawable, const ActorUID &actor);
		DrawableObjTree(std::unique_ptr<DrawableObject> drawable, std::vector<std::unique_ptr<DrawableObject>> frontchildren, std::vector<std::unique_ptr<DrawableObject>> backchildren);
		void removeChild(std::shared_ptr<DrawableObjTree> childBase);
		void addBackChild(std::shared_ptr<DrawableObjTree> childBase);
		void addFrontChild(std::shared_ptr<DrawableObjTree> childBase);

		void draw(Renderer& renderer, sf::RenderStates states);

		std::unique_ptr<DrawableObject> drawable;

		std::vector<std::shared_ptr<DrawableObjTree>> frontchildren;
		std::vector<std::shared_ptr<DrawableObjTree>> backchildren;

		ActorUID actor;
	};
}