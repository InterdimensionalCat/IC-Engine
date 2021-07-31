#pragma once
#include "include.h"
#include "InputHandle.h"
#include "Renderer.h"
#include <SFML\Graphics.hpp>



namespace ic::gfx {

	class GfxTest {
	public:
		GfxTest() {
			//LOAD DATA HERE
			shape.setPosition(sf::Vector2f(100.0f, 100.0f));
			shape.setRadius(30.0f);
			shape.setFillColor(sf::Color::Green);
		}

		void update(ic::InputHandle& input) {
			//UPDATE DATA HERE
			if (input.isDown(sf::Keyboard::D)) {
				shape.setPosition(shape.getPosition() + sf::Vector2f(1.0f, 0.0f));
			}
		}

		void draw(ic::gfx::Renderer& renderer) {
			//DRAW DATA HERE
			renderer.getWindow()->draw(shape);
		}

		sf::CircleShape shape;
	};
}
