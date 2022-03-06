#pragma once
#include <SFML\Graphics.hpp>

namespace ic {
	struct KeyboardPressKeyEvent {
		sf::Keyboard::Key keycode;
	};

	struct KeyboardReleaseKeyEvent {
		sf::Keyboard::Key keycode;
	};
}