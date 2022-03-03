#include "include.h"
#include "MenuButton.h"
#include "Renderer.h"
#include "Window.h"

using namespace ic;

void MenuButton::draw(const float interpol) {
	//sf::Text text(button_text, font);

	Renderer::get()->window->window->draw(*text_obj);
	Renderer::get()->window->window->draw(
		boundingBox.makeDrawableSFMLRect(2.0f,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 255)));
}