#pragma once

namespace ic {
	class Window;

	class WindowEventListener
	{
	public:
		WindowEventListener();
		virtual bool handleWindowEvent(const sf::Event& event) = 0;
		virtual void update(Window& window) = 0;
	};
}


