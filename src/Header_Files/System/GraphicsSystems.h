#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Window.h"
#include "Renderer.h"

namespace ic {
	class DrawSprites : public SystemTrivial<SpriteDrawable> {
	public:
		DrawSprites(GameScene* scene) : SystemTrivial(scene), window(Renderer::get()->window) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto sprite = scene->compManager->getComponent<SpriteDrawable>(entry);
			sprite->spr->setTexture(sprite->tex->getTexture());
			window->window->draw(*sprite->spr);
		}

		_System(DrawSprites, SystemType::Graphics);

	private:
		std::shared_ptr<Window> window;
	};

	class UpdateSpritePos : public SystemTrivial<SpriteDrawable, Transform> {
	public:
		UpdateSpritePos(GameScene* scene) : SystemTrivial(scene) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto sprite = scene->compManager->getComponent<SpriteDrawable>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			sf::Sprite& spr = *sprite->spr;
			spr.setPosition(s2d::Point2p(trans->x, trans->y).toSFMLVec());
			//spr.setPosition(s2d::toPixels(trans->x), s2d::toPixels(trans->y));
		}

		_System(UpdateSpritePos, SystemType::PreGraphics);
	};

	class DrawAnimations : public SystemTrivial<Animatable> {
	public:
		DrawAnimations(GameScene* scene) : SystemTrivial(scene), window(Renderer::get()->window) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto anim = scene->compManager->getComponent<Animatable>(entry);
			anim->animation->draw(*window);
		}
	private:
		std::shared_ptr<Window> window;

		_System(DrawAnimations, SystemType::Graphics);
	};

	class StateAnimationDriver : public SystemTrivial<Animatable, Transform, StateController, Velocity, AnimStateMap, Hitbox, InputController> {
	public:
		StateAnimationDriver(GameScene* scene) : SystemTrivial(scene) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto anim = scene->compManager->getComponent<Animatable>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			auto vel = scene->compManager->getComponent<Velocity>(entry);
			auto state = scene->compManager->getComponent<StateController>(entry);
			auto statemap = scene->compManager->getComponent<AnimStateMap>(entry);

			//change anim based on state
			if (statemap->prevstate != state->state) {
				statemap->prevstate = state->state;
				bool prevflip = anim->animation->isFlipped();
				anim->animation = std::make_shared<Animation>(statemap->animations->at(state->state), prevflip);
			}

			//determine if it needs to be flipped
			if (state->state == ActionState::GroundMove || state->state == ActionState::GroundTurn || state->state == ActionState::GroundStill) {

				if (state->state == ActionState::GroundStill) {
					auto input = scene->compManager->getComponent<InputController>(entry);
					if (input->input->isDown(InputButton::LEFT) && !anim->animation->isFlipped()) {
						anim->animation->setFlipped(true);
					}

					if (input->input->isDown(InputButton::RIGHT) && anim->animation->isFlipped()) {
						anim->animation->setFlipped(false);
					}
				}

				if (anim->animation->isFlipped() && vel->x > 0) {
					anim->animation->setFlipped(false);
				}

				if (!anim->animation->isFlipped() && vel->x < 0) {
					anim->animation->setFlipped(true);
				}
			}

			//update animation position
			auto hitbox = scene->compManager->getComponent<Hitbox>(entry)->rect;
			
			hitbox += s2d::Vec2m(trans->x, trans->y);
			//hitbox.top += trans->y;
			//hitbox.left += trans->x;

			auto width = anim->animation->getDimensions().x;
			auto height = anim->animation->getDimensions().y;
			auto center = sf::Vector2f(s2d::Point2p(hitbox.center()).toSFMLVec());
			center -= sf::Vector2f(width / 2.0f, height / 2.0f);
			//anim->animation->setPosition(sf::Vector2f(s2d::toPixels(center.x - width / 2.0f), s2d::toPixels(hitbox.top + hitbox.height - height)));
			anim->animation->setPosition(
				sf::Vector2f(center.x, 
					(float)s2d::Pixels(hitbox.max.y) - height)
			);
			anim->animation->update();
		}

		_System(StateAnimationDriver, SystemType::PreGraphics);
	};
}