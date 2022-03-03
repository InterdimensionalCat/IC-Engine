#pragma once
#include "System.h"
#include "SFML/Graphics.hpp"
#include "Window.h"

namespace ic {
#ifdef _DEBUG
	template<typename... ComponentTypes>
	class DebugGraphicsSystem : public System {
	public:
		DebugGraphicsSystem(GameScene* scene) : System(scene), window(Renderer::get()->window),
			view(std::make_shared<SceneView<ComponentTypes...>>(scene)) {}

		virtual void excecute() {
			BenchmarkLogger::get()->beginBenchmark(this->getName());
			for (auto actor : *view) {
				if (Settings::getDebug()) {
					excecutionFunction(actor);
				}
			}
			BenchmarkLogger::get()->endBenchmark(this->getName());
		}
	protected:
		DebugGraphicsSystem() {}
		virtual void excecutionFunction(std::shared_ptr<ActorEntry> entry) = 0;

		virtual std::string toString() const override {
			std::string types[] = { "", (typeid(ComponentTypes).name())... ,"" };
			std::string printval = getName()
				+ ":(DebugGraphicsSystem<";

			for (auto str : types) {
				std::string::size_type i = str.find("struct");
				if (i != std::string::npos) {
					str.erase(i, 6);
				}

				printval += str;
			}

			printval += " >)->Type="
				+ getSysTypeName();
			return printval;
		}

		std::shared_ptr<Window> window;
		std::shared_ptr<SceneView<ComponentTypes...>> view;
	};

	class DisplayHitboxes : public DebugGraphicsSystem<Transform, Hitbox> {
	public:
		DisplayHitboxes(GameScene* scene) : DebugGraphicsSystem(scene) {}
		void excecutionFunction(std::shared_ptr<ActorEntry> entry) override {
			auto trans = getComponent<Transform>(entry);
			auto hitbox = getComponent<Hitbox>(entry);
			s2d::Rect2p aabb = (s2d::Rect2p)hitbox->rect;
			aabb += s2d::Vec2p(trans->x, trans->y);

			window->window->draw(aabb.makeDrawableSFMLRect(
				2.0, sf::Color(0, 0, 0, 0), sf::Color::Red
			));

			auto aabbextension = getComponent<HitboxExtension>(entry);
			if (aabbextension != nullptr) {
				s2d::Rect2p aabbBig = (s2d::Rect2p)aabbextension->rect;

				aabbBig += s2d::Vec2p(trans->x, trans->y - aabbBig.height() / 2.0_px);

				window->window->draw(aabbBig.makeDrawableSFMLRect(
					2.0, sf::Color(0, 0, 0, 0), sf::Color::Green
				));
			}
		}
	private:
		_System(DisplayHitboxes, SystemType::PostGraphics);
	};

#endif
}
