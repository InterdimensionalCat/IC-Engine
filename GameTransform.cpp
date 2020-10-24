#include "include.h"
#include "GameTransform.h"

void GameTransform::translate(const Vector2f trans) { 
	//prevpos = pos;
	pos += trans; 
	upd = false;
}

void GameTransform::setPos(const Vector2f newpos) { 
	//prevpos = newpos;
	pos = newpos; 
	upd = false;
}

void GameTransform::setPos(const float x, const float y) { 
	pos = Vector2f(x, y); 
	//prevpos = pos;
	upd = false;
}

Vector2f GameTransform::forward() const {
	return fwd;
}

Vector2f GameTransform::up() const {
	return upvec;
}

Vector2f GameTransform::down() const {
	return -upvec;
}

Vector2f GameTransform::back() const {
	return -fwd;
}

void GameTransform::start() {

}

void GameTransform::tick(InputHandle* input) {
	prevpos = pos;
}

void GameTransform::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//draw the point if in debug mode
	if (instance->debug) {
		CircleShape shape;
		shape.setRadius(3);
		shape.setFillColor(Color::Cyan);
		shape.setOutlineColor(Color::Cyan);
		shape.setPosition(lerp(prevpos, pos, instance->renderer->interpol));
		target.draw(shape, states);
	}
}

bool GameTransform::updated() {
	return upd;
}

void GameTransform::setupdated() {
	upd = true;
}