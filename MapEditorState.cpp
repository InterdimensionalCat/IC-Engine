#include "include.h"
#include "MapEditorState.h"
#include "TileSet.h"
#include "TileEditor.h"
#include "Camera.h"

 void MapEditorState::MapEditorState::init() {

}

 void MapEditorState::enter() {
	 working_tileset = make_unique<TileSet>("test");
	 working_tileset->start();
	 RenderWindow* wind = new RenderWindow(sf::VideoMode(instance->WIDTH / 2, instance->HEIGHT / 2), "TEST");
	 RenderWindow* wind1 = new RenderWindow(sf::VideoMode(instance->WIDTH / 2, instance->HEIGHT / 2), "TIle Edit");
	 instance->subwindows.emplace("TEST", make_unique<WindowData>(wind));
	 instance->subwindows.emplace("TILES", make_unique<WindowData>(wind1));
	 tileeditor = make_unique<TileEditor>(working_tileset.get(), &working_tileset->tiles.at(1).at(0), instance->subwindows.at("TILES")->get());
	 camera = make_unique<Camera>();
	 camera->start();
}
 void MapEditorState::tick(InputHandle* input) {

	 camera->tick(input);

	 if (input->isDown(Keyboard::Right)) {
		 camera->move(Vector2f(0.2 * 60, 0));
	 }

	 if (input->isDown(Keyboard::Left)) {
		 camera->move(Vector2f(-0.2 * 60, 0));
	 }

	 if (input->isDown(Keyboard::Up)) {
		 camera->move(Vector2f(0, -0.2 * 60));
	 }

	 if (input->isDown(Keyboard::Down)) {
		 camera->move(Vector2f(0, 0.2 * 60));
	 }

	 if (input->isDown(Keyboard::O)) {
		 camera->rotate(-1.0f);
	 }

	 if (input->isDown(Keyboard::P)) {
		 camera->rotate(1.0f);
	 }

	 if (input->isDown(Keyboard::K)) {
		 camera->zoom(-0.01f);
	 }

	 if (input->isDown(Keyboard::L)) {
		 camera->zoom(0.01f);
	 }

	 if (input->isDown(Keyboard::R)) {
		 camera->reset();
	 }

	 if (input->isPressed(Mouse::Left)) {
		 Mouse::getPosition(*input->getWindowData("TEST")->get());
		 editing = true;
	 }

	 //tileeditor->tick(input);
}
 void MapEditorState::draw(Renderer* renderer) {
	 working_tileset->draw(*renderer->getWindowData("TEST")->get(), renderer->getWindowData("TEST")->states);
	 if (editing) {
		 tileeditor->draw(*renderer->getWindowData("TILES")->get(), renderer->getWindowData("TILES")->states);
		 camera->draw(*renderer->getWindowData("TILES")->get(), renderer->getWindowData("TILES")->states);
	 }
	 else {
		 camera->draw(*renderer->getWindowData("TEST")->get(), renderer->getWindowData("TEST")->states);
	 }
}
 void MapEditorState::exit() {

}