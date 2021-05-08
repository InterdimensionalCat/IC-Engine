#include "DrawableObjTree.h"


using namespace ic::gfx;

DrawableObjTree::DrawableObjTree(std::unique_ptr<DrawableObject> drawable, const ic::ActorUID actor) : drawable(std::move(drawable)), actor(actor) {

}


void DrawableObjTree::removeChild(std::shared_ptr<DrawableObjTree> childBase) {
	frontchildren.erase(std::remove(frontchildren.begin(), frontchildren.end(), childBase), frontchildren.end());
	backchildren.erase(std::remove(backchildren.begin(), backchildren.end(), childBase), backchildren.end());
    childBase->parent.reset();
}

void DrawableObjTree::addBackChild(std::shared_ptr<DrawableObjTree> childBase) {
	backchildren.push_back(childBase);
    childBase->parent = actor;
}

void DrawableObjTree::addFrontChild(std::shared_ptr<DrawableObjTree> childBase) {
	frontchildren.push_back(childBase);
    childBase->parent = actor;
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