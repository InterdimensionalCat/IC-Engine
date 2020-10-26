#include "include.h"
#include "Camera.h"
#include "GameTransform.h"

void Camera::start() {
	transform = addBehavior<GameTransform>();

	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0f;
	prevrotation = 0.0f;

	Actor::start();
}

void Camera::tick(InputHandle* input) {
	prevscale = scale;
	prevrotation = rotation;
	Actor::tick(input);
}

void Camera::draw(sf::RenderTarget& target, sf::RenderStates states) const {


	View newview = target.getDefaultView();

	newview.setCenter(lerp(transform->getPrevPos(), transform->getPos(), instance->renderer->interpol));
	newview.setRotation(lerp(prevrotation, rotation, instance->renderer->interpol));
	newview.zoom(lerp(prevscale, scale, instance->renderer->interpol));

	target.setView(newview);

	Actor::draw(target, states);
}

void Camera::move(Vector2f trans) {
	transform->translate(trans);
}

void Camera::setPos(Vector2f newpos) {
	transform->setPos(newpos);
}

void Camera::rotate(const float &rotation) {
	this->rotation += rotation;
}

void Camera::zoom(const float &scale) {
	this->scale += scale;
}

void Camera::reset() {
	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0f;
	prevrotation = 0.0f;
	transform->setPos(Vector2f(0, 0));
}

void Camera::reset(Vector2f pos) {
	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0f;
	prevrotation = 0.0f;
	transform->setPos(pos);
}
