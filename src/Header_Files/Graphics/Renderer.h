#pragma once
#include "Window.h"


namespace ic {

	class Window;

	class Renderer {

	public:
		Renderer() {
		}


		void preRender() {
			//this->interpol = interpol;
			Window::get()->clear();
			//window->clear(sf::Color(255, 255, 255, 255));
			//ImGui::SFML::Update(*window, guiClock.restart());
		}

		void renderGui() {
			//ImGui::SFML::Render(*window);
		}


		void postRender() {
			Window::get()->display();
			//window->display();
		}

		void draw() {

		}

		static Renderer* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<Renderer>();
			}
			return instance.get();
		}

		sf::RenderStates states = sf::RenderStates::Default;

	private:

		inline static std::unique_ptr<Renderer> instance;
	};
}