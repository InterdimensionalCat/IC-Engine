#include "include.h"
#include "MenuState.h"
#include "GameEngine2020.h"

MenuState::MenuState(StateManager* p) : State(p) {

	auto center = s2d::ScreenUnits::Point((float)parent->instance->WIDTH / 2, 200.0f);

	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "fonts";
	filepath /= "terminat";
	filepath += ".ttf";

	if (!titleFont.loadFromFile(filepath.generic_u8string())) {
#ifdef _DEBUG
		throw TextureLoadException("terminat", filepath.generic_u8string());
#endif
	}
	title = Text(parent->instance->TITLE, titleFont);
	title.setCharacterSize(120);
	title.setFillColor(Color(50, 50, 50));
	title.setOutlineColor(Color::Black);
	title.setOutlineThickness(5);
	title.setStyle(Text::Regular);
	Vector2f size = Vector2f(title.getGlobalBounds().width, title.getGlobalBounds().height);
	Vector2f topLeft = center.toSFMLVec<float>() - size / 2.0f;
	title.setPosition(topLeft);
	//title.setPosition(center.toSFMLVec<float>());
	//title.setOrigin(center.toSFMLVec<float>());

	title.setStyle(Text::Bold);
	title.setFillColor(Color(5, 5, 5));
}

void MenuState::init() {
	buttons[0] = std::make_shared<MenuButton>(s2d::ScreenUnits::Point((float)parent->instance->WIDTH / 2, 400.0f), "Game", "terminat", 100.0f, this);
	buttons[1] = std::make_shared<MenuButton>(s2d::ScreenUnits::Point((float)parent->instance->WIDTH / 2, 600.0f), "Map Editor", "terminat", 100.0f, this);
	buttons[2] = std::make_shared<MenuButton>(s2d::ScreenUnits::Point((float)parent->instance->WIDTH / 2, 800.0f), "Exit", "terminat", 100.0f, this);
	for (auto& b : buttons) {
		instance->input->addListener((std::shared_ptr<EventListener>)b);
	}
}

void MenuState::enter() {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->active = true;
	}
}

void MenuState::tick(InputHandle* input) {

}

void MenuState::select(std::string pressedButtonName) {

#ifdef _DEBUG
	cout << pressedButtonName << "!\n";
#endif

	if (pressedButtonName == "Game") {
		parent->setState("GAME");
	}

	if (pressedButtonName == "Map Editor") {
		parent->setState("MAPEDITOR");
	}

	if (pressedButtonName == "Exit") {
		parent->instance->stop();
	}
}

void MenuState::exit() {
	for (int i = 0; i < buttons.size(); i++) {
		//instance->input->removeListener(buttons[i]);
		buttons[i]->active = false;
	}
};

void MenuState::draw(Renderer* renderer) {

	RenderWindow* wind = renderer->window.get();
	auto& states = renderer->states;

	wind->draw(title, states);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->draw(renderer);
	}
}