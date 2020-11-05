#include "include.h"
#include "GameTransform.h"


using namespace s2d;

void GameTransform::translate(const Vec& trans) {
	pos += trans; 
}

void GameTransform::setPos(const Point& newpos) {
	pos = newpos; 
}

void GameTransform::setPos(const float x, const float y) { 
	pos = Point(x, y);
}

NormalVec GameTransform::forward() const {
	return fwd;
}

NormalVec GameTransform::up() const {
	return upvec;
}

NormalVec GameTransform::down() const {
	return -upvec;
}

NormalVec GameTransform::back() const {
	return -fwd;
}

void GameTransform::start() {

}

void GameTransform::tick(std::shared_ptr<InputHandle>& input) {
	prevpos = pos;
}

void GameTransform::draw(std::shared_ptr<Renderer>& renderer) {

	auto target = renderer->window.get();
	auto states = renderer->states;

	//draw the point if in debug mode
	if (instance->debug) {
		CircleShape shape;
		shape.setRadius(3);
		shape.setFillColor(Color::Cyan);
		shape.setOutlineColor(Color::Cyan);
		shape.setPosition(lerp(prevpos.toSFMLVec<float>() - Vector2f(1.5f, 1.5f), pos.toSFMLVec<float>() - Vector2f(1.5f, 1.5f), renderer->interpol));
		target->draw(shape, states);
	}
}