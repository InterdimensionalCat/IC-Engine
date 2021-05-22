#include "DrawableObjTree.h"
#include "LoggerProvider.h"

using namespace ic::gfx;

DrawableObjTree::DrawableObjTree(std::unique_ptr<DrawableObject> drawable, const ic::ActorUID actor) : drawable(std::move(drawable)), actor(actor) {

}

void DrawableObjTree::removeChild(std::shared_ptr<DrawableObjTree> childBase) {
    auto foundFront = std::find(frontchildren.begin(), frontchildren.end(), childBase);
    auto foundBack = std::find(backchildren.begin(), backchildren.end(), childBase);
    if (foundFront == frontchildren.end() && foundBack == frontchildren.end()) {
        //crash if child doesnt exist in this tree
        LoggerProvider::logAndThrowLogicError(childBase->actor.toString() + " is not a child of tree" + this->actor.toString() + "\n", LogSeverity::Fatal, LogType::Rendering);
    }
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

    //apply the reletive origin to both the children and the node
    //other renderstates like blend mode might not apply to front children
    //when it is implemented

    states.transform *= ((sf::Transformable*)this)->getTransform();
    for (auto& obj : backchildren) {
        obj->draw(renderer, states);
    }

    drawable->draw(renderer, states);

    for (auto& obj : frontchildren) {
        obj->draw(renderer, states);
    }
}