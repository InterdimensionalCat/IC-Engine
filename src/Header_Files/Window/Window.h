#pragma once

namespace ic {

	class Window
	{
	public:

		Window(const Window& other) = delete;
		Window& operator=(const Window& rhs) = delete;

		~Window();

		bool pollEvents();
		void clear();
		void display();

		//bool updateInput();
		//void preRender(const float interpol);
		//void renderGui();
		//void postRender();
		//void registerWindowEventListener(std::shared_ptr<WindowEventListener> listener);

		//float interpol = 0.0f;
		//sf::RenderStates states = sf::RenderStates::Default;
		//std::unique_ptr<sf::RenderWindow> window;

		static ic::Window* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<ic::Window>();
			}
			return instance.get();
		}

		std::unique_ptr<sf::RenderWindow> window;

	private:
		Window();

	private:

		inline static std::unique_ptr<ic::Window> instance;
		//std::vector<std::shared_ptr<WindowEventListener>> listeners;
		//sf::Clock guiClock;
	};
}


