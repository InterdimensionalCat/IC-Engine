#include "include.h"
#include "Camera.h"

using Point = s2d::GameUnits::Point;
using Vec = s2d::GameUnits::Vec;
using Rectangle = s2d::GameUnits::Rectangle;

void Camera::start() {

	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0_rad;
	prevrotation = 0.0_rad;
	pos = s2d::PixelUnits::Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	prevpos = s2d::PixelUnits::Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	s2d::ScreenUnits::transform_ratio = s2d::ScreenUnits::defaultTransform();

	Actor::start();
}

void Camera::tick(InputHandle* input) {
	prevscale = scale;
	prevrotation = rotation;
	prevpos = pos;
	Actor::tick(input);
}

void Camera::draw(Renderer* renderer) {

	auto target = renderer->window.get();

	View newview = target->getDefaultView();

	newview.setCenter(lerp(prevpos.toSFMLVec<float>(), pos.toSFMLVec<float>(), renderer->interpol));
	newview.setRotation(lerp((float)prevrotation.get(), (float)rotation.get(), renderer->interpol));
	newview.zoom(lerp(prevscale, scale, renderer->interpol));

	target->setView(newview);

	Actor::draw(renderer);
}

void Camera::move(Vec trans) {
	pos += (s2d::PixelUnits::Vec)trans;
	update();
}

void Camera::setPos(Point newpos) {
	pos = (s2d::PixelUnits::Point)newpos;
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
	pos = s2d::PixelUnits::Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	prevpos = s2d::PixelUnits::Point(instance->WIDTH / 2.0f, instance->HEIGHT / 2.0f);
	s2d::ScreenUnits::transform_ratio = s2d::ScreenUnits::defaultTransform();
}

void Camera::reset(Point pos) {
	scale = 1.0f;
	prevscale = 1.0f;
	rotation = 0.0_rad;
	prevrotation = 0.0_rad;
	this->pos = (s2d::PixelUnits::Point)pos;
	prevpos = (s2d::PixelUnits::Point)pos;
	s2d::ScreenUnits::transform_ratio = s2d::ScreenUnits::defaultTransform();
}

void Camera::update() {
	auto& ratio = s2d::ScreenUnits::transform_ratio;
	ratio = s2d::ScreenUnits::defaultTransform();

	ratio.rotate(rotation);
	ratio.scale(scale, scale);
	ratio.translate(s2d::PixelUnits::Vec(pos.x, pos.y));
}


