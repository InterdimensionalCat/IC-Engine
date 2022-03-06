#include "include.h"
#include "Input.h"
#include "Window.h"

using namespace ic;

//std::map<std::string, InputFinder> Input::prototypeTable;

//KeyboardInput::KeyboardInput() {
//	inputMap.emplace(InputButton::UP,    sf::Keyboard::W    );
//	inputMap.emplace(InputButton::DOWN,  sf::Keyboard::S    );
//	inputMap.emplace(InputButton::LEFT,  sf::Keyboard::A    );
//	inputMap.emplace(InputButton::RIGHT, sf::Keyboard::D    );
//	inputMap.emplace(InputButton::JUMP, sf::Keyboard::Space );
//
//	inputMap.emplace(InputButton::AUDIO_1, sf::Keyboard::L  );
//	inputMap.emplace(InputButton::AUDIO_2, sf::Keyboard::O  );
//	inputMap.emplace(InputButton::AUDIO_3, sf::Keyboard::P  );
//}
//
//bool KeyboardInput::isDown(const InputButton key) const {
//	return handle.isDown(inputMap.at(key));
//}
//	
//
//bool KeyboardInput::isPressed(const InputButton key) const {
//	return handle.isPressed(inputMap.at(key));
//}