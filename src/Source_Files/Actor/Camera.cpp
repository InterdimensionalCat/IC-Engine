#include "include.h"
#include "Camera.h"

using namespace s2d;

void Camera::start() {

	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0_rad;
	prevrotation = 0.0_rad;
	pos = Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	prevpos = Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);

	Actor::start();
}

void Camera::tick(std::shared_ptr<InputHandle>& input) {
	prevscale = scale;
	prevrotation = rotation;
	prevpos = pos;
	Actor::tick(input);
}

void Camera::draw(std::shared_ptr<Renderer>& renderer) {

	auto target = renderer->window.get();

	View newview = target->getDefaultView();

	newview.setCenter(lerp(prevpos.toSFMLVec<float>(), pos.toSFMLVec<float>(), renderer->interpol));
	newview.setRotation(lerp((float)prevrotation.get(), (float)rotation.get(), renderer->interpol));
	newview.zoom(lerp(prevscale, scale, renderer->interpol));

	target->setView(newview);

	Actor::draw(renderer);
}

void Camera::move(const Vec& trans) {
	pos += (Vec)trans;
	update();
}

void Camera::setPos(const Point& newpos) {
	pos = (Point)newpos;
	update();
}

void Camera::rotate(const Radians &angle) {
	rotation += angle;
	this->update();
}

void Camera::zoom(const float &scale) {
	this->scale += scale;
	update();
}

void Camera::reset() {
	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0_rad;
	prevrotation = 0.0_rad;
	pos = Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	prevpos = Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
}

void Camera::reset(Point pos) {
	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0_rad;
	prevrotation = 0.0_rad;
	this->pos = (Point)pos;
	prevpos = (Point)pos;
}

void Camera::update() {

}


