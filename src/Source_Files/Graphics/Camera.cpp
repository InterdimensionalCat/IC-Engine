#include "include.h"
#include "Camera.h"
#include "Window.h"
#include "Components.h"
#include "Scene.h"
#include "ActorEntry.h"
#include "ComponentManager.h"

using namespace ic;
using namespace s2d;

Camera::Camera(const float width, const float height, std::shared_ptr<ActorEntry> followTarget, Scene* scene) : Camera(width, height, CameraMode::Follow) {
	Camera::scene = scene;
	Camera::followTarget = followTarget;

	auto trans = scene->compManager->getComponent<Transform>(followTarget);
	auto hitbox = scene->compManager->getComponent<Hitbox>(followTarget)->rect;

	//auto targetHitbox = sf::FloatRect(hitbox->rect.min.x + trans->x, hitbox->rect.min.y + trans->y, hitbox->rect.width, hitbox->rect.height);
	Rect2p targetHitbox = (Rect2p)(hitbox + Vec2m(trans->x, trans->y));

	Vec2p targetScrollPos = Vec2p(targetHitbox.center() - Vec2p(Settings::getWidth() / 2.0f, Settings::getHeight() / 2.0f));

	//sf::Vector2f targetScrollPos()
	//auto targetScrollPos = sf::Vector2f(s2d::toPixels(targetHitbox.left + targetHitbox.width / 2.0f) - Settings::getWidth() / 2.0f,
	//	s2d::toPixels(targetHitbox.top + targetHitbox.height / 2.0f) - (float)Settings::getHeight() / 2.0f);

	scrollpos = (sf::Vector2f)targetScrollPos;

	checkBounds();
}

Camera::Camera(const float width, const float height, const CameraMode& mode) : mode(mode) {
	boundsInPixels = sf::Vector2f(width, height);
}

void Camera::updateWindow(Window& window) {
	switch (mode) {
	case CameraMode::Controlled:
		controlled(window);
		break;
	case CameraMode::Follow:
		follow(window);
		break;
	case CameraMode::Stationary:
		stationary(window);
		break;
	}
}

void Camera::reset(Window& window, const sf::Vector2f pixelResetPos) {
	auto resetView = window.window->getDefaultView();
	resetView.move(pixelResetPos);
	window.window->setView(resetView);
}

void Camera::changeViewMode(const CameraMode& newmode, sf::Vector2f newpos, Window& window) {
	reset(window, newpos);
	mode = newmode;
}

void Camera::checkBounds() {
	if (scrollpos.x + Settings::getWidth() > boundsInPixels.x) {
		scrollpos.x = boundsInPixels.x - Settings::getWidth();
	}

	if (scrollpos.y + Settings::getHeight() > boundsInPixels.y) {
		scrollpos.y = boundsInPixels.y - Settings::getHeight();
	}

	if (scrollpos.x < 0) {
		scrollpos.x = 0;
	}

	if (scrollpos.y < 0) {
		scrollpos.y = 0;
	}

}

void Camera::controlled(Window& window) {

	window.window->setView(window.window->getDefaultView());
	auto newview = window.window->getView();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		scrollpos -= sf::Vector2f(5, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		scrollpos += sf::Vector2f(0, 5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		scrollpos += sf::Vector2f(5, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		scrollpos -= sf::Vector2f(0, 5);
	}

	checkBounds();

	newview.move(scrollpos);

	window.window->setView(newview);
}

void Camera::follow(Window& window) {

	window.window->setView(window.window->getDefaultView());
	auto newview = window.window->getView();

	auto trans = scene->compManager->getComponent<Transform>(followTarget);
	auto hitbox = scene->compManager->getComponent<Hitbox>(followTarget)->rect;

	Rect2p targetHitbox = (Rect2p)(hitbox + Vec2m(trans->x, trans->y));

	Vec2p targetScrollPos = Vec2p(targetHitbox.center() - Vec2p(Settings::getWidth() / 2.0f, Settings::getHeight() / 2.0f));


	auto dist = (sf::Vector2f)targetScrollPos -
		scrollpos;


	//Logger::get() << "dist: " << dist.x << ", " << dist.y << "\n";

	//float scrollDivisorX = 1.0f;
	//float scrollDivisorY = 1.0f;


	//float baseDivisor = 60.0f;

	//float maxDist = 200.0f;

	//if (abs(dist.x) < maxDist) {
	//	float scrollDivisorX = baseDivisor - (baseDivisor -1.0f)*(abs(dist.x) / maxDist);
	//}

	//if (abs(dist.y) < maxDist) {
	//	float scrollDivisorY = baseDivisor - (baseDivisor -1.0f)*(abs(dist.y) / maxDist);
	//}

	//scrollpos += dist / 15.0f;

	scrollpos += dist / (15.0f / 2.0f);

	//scrollpos += sf::Vector2f(dist.x / scrollDivisorX, dist.y / scrollDivisorY);

	dist = (sf::Vector2f)targetScrollPos -
		scrollpos;

	if (sqrt(dist.x * dist.x + dist.y * dist.y) <= 2.0f) {
		scrollpos = (sf::Vector2f)targetScrollPos;
	}


	checkBounds();

	//scrollpos = sf::Vector2f(round(scrollpos.x), round(scrollpos.y));
	scrollpos = sf::Vector2f(scrollpos.x, scrollpos.y);

	newview.move(scrollpos);
	window.window->setView(newview);
}

void Camera::stationary(Window& window) {

}