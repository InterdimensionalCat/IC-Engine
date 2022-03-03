#pragma once
#include "WindowEventListener.h"

namespace ic {

	class ButtonCallbackBase {
	public:
		template<typename... Args>
		ButtonCallbackBase() {}
		virtual void operator()() {}
	};

	template<typename... Args>
	class ButtonCallback : public ButtonCallbackBase {
	public:
		ButtonCallback(void(*callback)(Args...), Args... args) :
			callback_fn(callback), args(args...)
		{

		}

		void operator()() {
			std::apply(callback_fn, args);
			//callback_fn(args);
		}
	private:
		void (*callback_fn)(Args...);
		std::tuple<Args...> args;
	};


	class MenuButton : public WindowEventListener {
	public:
		template<typename... Args>
		MenuButton(const s2d::Vec2p &pos, const std::string& text,
			void(*callback)(Args...), Args... args) :
			button_text(text),
			callback(std::make_unique<ButtonCallback<Args...>>(
				callback, args...)
			) {

			//set up the file path of the texture
			fs::path filepath(fs::current_path());
			filepath /= "resources";
			filepath /= "fonts";
			filepath /= "cour";
			filepath += ".ttf";

			font = std::make_unique<sf::Font>();

			if (!font->loadFromFile(filepath.string())) {
#ifdef _DEBUG
				throw std::exception();
#endif
			}

			text_obj = std::make_unique<sf::Text>(button_text, *font);

			text_obj->setColor(sf::Color::Red);
			text_obj->setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
			text_obj->setStyle(sf::Text::Style::Bold);

			boundingBox = s2d::Rect2p(text_obj->getGlobalBounds().top,
				text_obj->getGlobalBounds().left,
				text_obj->getGlobalBounds().left + 
				text_obj->getGlobalBounds().width,
				text_obj->getGlobalBounds().top + 
				text_obj->getGlobalBounds().height);
		}
		void update() {}

		void draw(const float interpol);

		std::string getName() const override {
			return "GameButton";
		}

		bool handleWindowEvent(const sf::Event& event) override {
			if (event.type == sf::Event::MouseButtonPressed) {
				s2d::Point2p mousecoords = s2d::Point2p(
					event.mouseButton.x,
					event.mouseButton.y);

				if (boundingBox.contains(mousecoords)) {
					Logger::debug("Button \"{}\" Clicked!", button_text);
					click();

				}
			}

			return false;
		}

		void click() {
			(*callback)();
		}

		void update(Window& window) override {
			return;
		}
	private:
		std::string button_text;
		std::unique_ptr<ButtonCallbackBase> callback;
		std::unique_ptr<sf::Text> text_obj;
		std::unique_ptr<sf::Font> font;
		s2d::Rect2p boundingBox;
	};
}