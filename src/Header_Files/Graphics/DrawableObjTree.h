#pragma once
#include <vector>
#include <memory>
#include "DrawableObject.h" 

namespace ic::gfx {
	class DrawableObjTree {
	public:
		DrawableObjTree(std::unique_ptr<DrawableObject> drawable);
		DrawableObjTree(std::unique_ptr<DrawableObject> drawable, std::vector<std::unique_ptr<DrawableObject>> frontchildren, std::vector<std::unique_ptr<DrawableObject>> backchildren);
		void removeChild(std::shared_ptr<DrawableObjTree> childBase);
		void addBackChild(std::shared_ptr<DrawableObjTree> childBase);
		void addFrontChild(std::shared_ptr<DrawableObjTree> childBase);

		void draw(Renderer& renderer, sf::RenderStates states);

		std::unique_ptr<DrawableObject> drawable;

		std::vector<std::shared_ptr<DrawableObjTree>> frontchildren;
		std::vector<std::shared_ptr<DrawableObjTree>> backchildren;
	};
}