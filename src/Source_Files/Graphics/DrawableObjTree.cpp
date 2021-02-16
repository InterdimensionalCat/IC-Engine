#include "DrawableObjTree.h"


using namespace ic::gfx;

DrawableObjTree::DrawableObjTree(std::unique_ptr<DrawableObject> drawable) : drawable(std::move(drawable)), actor(actor) {

}

DrawableObjTree::DrawableObjTree(std::unique_ptr<DrawableObject> drawable, std::vector<std::unique_ptr<DrawableObject>> frontchildren, std::vector<std::unique_ptr<DrawableObject>> backchildren)
    : drawable(std::move(drawable)) {

    for (auto& child : frontchildren) {
        DrawableObjTree::frontchildren.push_back(std::make_shared<DrawableObjTree>(std::move(child)));
    }

    for (auto& child : backchildren) {
        DrawableObjTree::backchildren.push_back(std::make_shared<DrawableObjTree>(std::move(child)));
    }
}

void DrawableObjTree::removeChild(std::shared_ptr<DrawableObjTree> childBase) {
	frontchildren.erase(std::remove(frontchildren.begin(), frontchildren.end(), childBase), frontchildren.end());
	backchildren.erase(std::remove(backchildren.begin(), backchildren.end(), childBase), backchildren.end());
}

void DrawableObjTree::addBackChild(std::shared_ptr<DrawableObjTree> childBase) {
	backchildren.push_back(childBase);
}

void DrawableObjTree::addFrontChild(std::shared_ptr<DrawableObjTree> childBase) {
	frontchildren.push_back(childBase);
}

void DrawableObjTree::draw(Renderer& renderer, sf::RenderStates states) {

    states.transform *= ((sf::Transformable*)this)->getTransform();
    for (auto& obj : backchildren) {
        obj->draw(renderer, states);
    }

    drawable->draw(renderer, states);

    for (auto& obj : frontchildren) {
        obj->draw(renderer, states);
    }
}