#include "include.h"
#include "MenuState.h"
#include "GameEngine2020.h"


MenuState::MenuState(StateManager* p) : State(p), title(Button(parent->instance->TITLE, "terminat", Vector2f(parent->instance->WIDTH / 2, 200))) {
	title.option.setStyle(Text::Bold);
	title.option.setFillColor(Color(5, 5, 5));
	options.reserve(3);
}

void MenuState::init() {
	currentSelection = 0;
	options.emplace_back("Game", "terminat", Vector2f(parent->instance->WIDTH / 2, 400));
	options.emplace_back("Map Editor", "terminat", Vector2f(parent->instance->WIDTH / 2, 600));
	options.emplace_back("Exit", "terminat", Vector2f(parent->instance->WIDTH / 2, 800));
	options.at(currentSelection).hovered();
}

void MenuState::tick(InputHandle* input) {
	if (--clickDelay <= 0) {
		clickDelay = 0;
		//move up
		if (input->isPressed(Keyboard::W) ||
			input->isPressed(Keyboard::Up)) {
			clickDelay = 5;
			options.at(currentSelection).unhovered();
			currentSelection--;
			if (currentSelection < 0) {
				currentSelection = options.size() - 1;
			}
			options.at(currentSelection).hovered();

		}

		//move down
		if (input->isPressed(Keyboard::S) ||
			input->isPressed(Keyboard::Down)) {
			clickDelay = 5;
			options.at(currentSelection).unhovered();
			currentSelection++;
			if (currentSelection >= options.size()) {
				currentSelection = 0;
			}
			options.at(currentSelection).hovered();
		}
	}

	if (input->isPressed(Keyboard::Enter)) {
		select();
	}

	Vector2f mousecoords = (Vector2f)Mouse::getPosition(*input->getWindowData()->get());
	for (unsigned int i = 0; i < options.size(); i++) {
		if (options.at(i).hitbox.contains(mousecoords)) {
			options.at(currentSelection).unhovered();
			currentSelection = i;
			options.at(currentSelection).hovered();
			if (input->isPressed(Mouse::Left)) {
				select();
			}
		}
	}
}

void MenuState::select() {
	auto &b = options.at(currentSelection);
	b.selected();
#ifdef _DEBUG
	cout << (std::string)b.option.getString() << "!\n";
#endif

	if (b.option.getString().toAnsiString() == "Game") {
		parent->setState("GAME");
	}

	if (b.option.getString().toAnsiString() == "Map Editor") {
		parent->setState("MAPEDITOR");
	}

	if (b.option.getString().toAnsiString() == "Exit") {
		parent->instance->stop();
	}
}

void MenuState::draw(Renderer* renderer) {

	auto wind = renderer->getWindowData()->get();
	auto& states = renderer->getWindowData()->states;

	wind->draw(title, states);

	for (auto &b : options) {
		wind->draw(b, states);

		//draw the hitbox in debug mode
		if (parent->instance->debug) {
			auto hitbox = b.hitbox;
			RectangleShape hbox;
			hbox.setPosition(Vector2f(hitbox.left, hitbox.top));
			hbox.setSize(Vector2f(hitbox.width, hitbox.height));
			hbox.setOutlineColor(Color::Red);
			hbox.setFillColor(Color::Transparent);
			hbox.setOutlineThickness(3);
			wind->draw(hbox, states);
		}
	}
}