#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Window.h"
#include "MtSystem.h"

namespace ic {
	class DrawSprites : public SystemTrivial<SpriteDrawable> {
	public:
		DrawSprites(Scene* scene) : SystemTrivial(scene), window(scene->window) {}

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
		UpdateSpritePos(Scene* scene) : SystemTrivial(scene) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto sprite = scene->compManager->getComponent<SpriteDrawable>(entry);
			auto trans = scene->compManager->getComponent<Transform>(entry);
			sf::Sprite& spr = *sprite->spr;
			spr.setPosition(s2d::toPixels(trans->x), s2d::toPixels(trans->y));
		}

		_System(UpdateSpritePos, SystemType::PreGraphics);
	};

	class DrawAnimations : public SystemTrivial<Animatable> {
	public:
		DrawAnimations(Scene* scene) : SystemTrivial(scene), window(scene->window) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto anim = scene->compManager->getComponent<Animatable>(entry);
			anim->animation->draw(*window);
		}
	private:
		std::shared_ptr<Window> window;

		_System(DrawAnimations, SystemType::Graphics);
	};

	class StateAnimationDriver : public MtSystem<Animatable, Transform, StateController, Velocity, AnimStateMap, Hitbox, InputController> {
	public:

		using compTypesTuple = std::tuple<Animatable*, Transform*, 
			StateController*, Velocity*, AnimStateMap*, Hitbox*, InputController*>;

		StateAnimationDriver(Scene* scene) : MtSystem(scene) {}

		void excecutionFunction(std::shared_ptr<ActorEntry> entry, compTypesTuple comps) override {
			auto anim = std::get<Animatable*>(comps);
			auto trans = std::get<Transform*>(comps);
			auto vel = std::get<Velocity*>(comps);
			auto state = std::get<StateController*>(comps);
			auto statemap = std::get<AnimStateMap*>(comps);

			auto hitbox = std::get<Hitbox*>(comps)->rect;
			auto input = std::get<InputController*>(comps);

			//change anim based on state
			if (statemap->prevstate != state->state) {
				statemap->prevstate = state->state;
				bool prevflip = anim->animation->isFlipped();
				anim->animation = std::make_shared<Animation>(statemap->animations->at(state->state), prevflip);
			}

			//determine if it needs to be flipped
			if (state->state == ActionState::GroundMove || state->state == ActionState::GroundTurn || state->state == ActionState::GroundStill) {

				if (state->state == ActionState::GroundStill) {
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

			hitbox.top += trans->y;
			hitbox.left += trans->x;

			auto width = s2d::toMeters(anim->animation->getDimensions().x);
			auto height = s2d::toMeters(anim->animation->getDimensions().y);
			auto center = sf::Vector2f(hitbox.left + hitbox.width / 2.0f, hitbox.top + hitbox.height / 2.0f);
			anim->animation->setPosition(sf::Vector2f(s2d::toPixels(center.x - width / 2.0f), s2d::toPixels(hitbox.top + hitbox.height - height)));
			anim->animation->update();
		}

		_System(StateAnimationDriver, SystemType::PreGraphics);
	};
}