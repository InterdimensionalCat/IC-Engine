#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <SFML\Graphics.hpp>
#include "InputEvent.h"
#include "Input.h"
#include "Port.h"
#include <algorithm>

namespace ic {

	enum class GameInputButton {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		JUMP,
		AUDIO_1,
		AUDIO_2,
		AUDIO_3
	};

	typedef std::function<std::shared_ptr<GameInputDevice>(const std::string&)> InputFinder;

	class GameInputDevice {
	public:
		virtual ~GameInputDevice() {}
		virtual void update() = 0;
		virtual bool isDown(const GameInputButton key) const = 0;
		virtual bool isPressed(const GameInputButton key) const = 0;
		virtual std::string getName() const = 0;
		std::shared_ptr<Port> getPort() const { return port; }

		virtual void pressKey(const GameInputButton key) = 0;
		virtual void releaseKey(const GameInputButton key) = 0;

	protected:


		GameInputDevice(const std::shared_ptr<Port> port) : port(port) {}
		std::shared_ptr<Port> port;
	};

	class GameKeyboardInput : public GameInputDevice {
	public:
		GameKeyboardInput(const uint32_t port) : GameInputDevice(port) {
			inputMap.emplace(sf::Keyboard::W, GameInputButton::UP);
			inputMap.emplace(sf::Keyboard::S, GameInputButton::DOWN);
			inputMap.emplace(sf::Keyboard::A, GameInputButton::LEFT);
			inputMap.emplace(sf::Keyboard::D, GameInputButton::RIGHT);
			inputMap.emplace(sf::Keyboard::Space, GameInputButton::JUMP);

			inputMap.emplace(sf::Keyboard::L, GameInputButton::AUDIO_1);
			inputMap.emplace(sf::Keyboard::O, GameInputButton::AUDIO_2);
			inputMap.emplace(sf::Keyboard::P, GameInputButton::AUDIO_3);
		}

		void update() override {
			keyboardListener.update();
		}

		bool isDown(const GameInputButton key) const override {
			return keyboardListener.isDown(key);
		}

		bool isPressed(const GameInputButton key) const override {
			return keyboardListener.isPressed(key);
		}

		void pressKey(KeyboardPressKeyEvent e) {
			keyboardListener.pressKey(inputMap.find(e.keycode)->second);
		}

		void releaseKey(KeyboardReleaseKeyEvent e) {
			keyboardListener.releaseKey(inputMap.find(e.keycode)->second);
		}

	private:
		KeyListener<GameInputButton> keyboardListener;
		std::map<sf::Keyboard::Key, GameInputButton> inputMap;
	};

	class GameInput {
	public:

		void update() {
			for (auto& device_vec : devices) {
				for (auto& device : device_vec.second) {
					device->update();
				}
			}
		}
		bool isDown(const GameInputButton key, const uint32_t port) {
			bool down = false;
			auto port_devices = devices.find(port);
			if (port_devices == devices.end()) {
				return false;
			}
			for (auto& device : port_devices->second) {
				if (device->isDown(key)) {
					down = true;
					currentDevices[port] = device;
					break;
				}
			}

			return down;
		}
		bool isPressed(const GameInputButton key, const uint32_t port) {
			bool pressed = false;
			auto port_devices = devices.find(port);
			if (port_devices == devices.end()) {
				return false;
			}
			for (auto& device : port_devices->second) {
				if (device->isPressed(key)) {
					pressed = true;
					currentDevices[port] = device;
					break;
				}
			}

			return pressed;
		}



		template<typename T, typename... Args>
		typename std::enable_if<std::is_base_of<GameInputDevice, T>::value, 
			std::shared_ptr<T>>::type registerGameInputDevice(const std::shared_ptr<Port> port, Args... Args) 
		{

			auto it = devices.find(port->value());
			if (it != devices.end()) {
				std::shared_ptr<T> device = std::make_shared<T>(std::forward(port, args));
				it->second.push_back(device);
				return device;
			}
			else {
				throw std::exception();
			}
		}

		template<typename T, typename... Args>
		typename std::enable_if<std::is_base_of<GameInputDevice, T>::value,
			std::shared_ptr<T>>::type registerGameInputDevice(Args... Args)
		{
			auto port = Port::createPort();
			std::shared_ptr<T> device = std::make_shared<T>(std::forward(port, args));
			devices.insert(std::pair(port->value(), device));
			return device;
		}


		void deregisterInputDevice(std::shared_ptr<GameInputDevice> device) {
			devices.erase(std::remove(devices.begin(), devices.end(), device), devices.end());
		}

		static GameInput* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<GameInput>();
			}
			return instance.get();
		}

	private:
		GameInput() {}
		inline static std::unique_ptr<GameInput> instance;
		std::map<uint32_t, std::vector<
			std::shared_ptr<GameInputDevice>>> devices;
		std::map<uint32_t, 
		std::shared_ptr<GameInputDevice>> currentDevices;
	};


//#ifndef _Input_Device
//#define _Input_Device(classtype) public:\
//static std::shared_ptr<GameInputDevice> create(const std::string& name) {\
//    return std::make_shared<classtype>();\
//}\
//std::string getName() const override { return #classtype; }\
//private:\
//class StartupObj {\
//public:\
//		StartupObj() {\
//			GameInputDevice::addPrototype( #classtype, create); \
//	}\
//}; \
//friend class StartupObj; \
//inline static StartupObj startup;
//#endif

	/*class KeyboardGlobal {
	public:

	private:
		friend class KeyboardHandle;
		friend class Window;

		class KeyboardGlobalEventListener : public WindowEventListener {
		public:

			bool handleWindowEvent(const sf::Event& event) {
				if (event.type == sf::Event::KeyPressed) {
					pressKey(event.key.code);
				}

				if (event.type == sf::Event::KeyReleased) {
					releaseKey(event.key.code);
				}

				return false;
			}

			void update(Window& window) {
				keylistener.update();
			}

			void pressKey(const sf::Keyboard::Key key) {
				keylistener.pressKey(key);
			}

			void releaseKey(const sf::Keyboard::Key key) {
				keylistener.releaseKey(key);
			}

			std::string getName() const override {
				return "KeyboardGlobalEventListener";
			}

			KeyListener<sf::Keyboard::Key> keylistener;
		};

		static bool isDown(sf::Keyboard::Key key) {
			return listener->keylistener.isDown(key);
		}

		static bool isPressed(sf::Keyboard::Key key) {
			return listener->keylistener.isPressed(key);
		}

		static inline std::shared_ptr<KeyboardGlobalEventListener> listener
			= std::make_shared<KeyboardGlobalEventListener>();
	};

	class KeyboardHandle {
	public:
		bool isDown(sf::Keyboard::Key key) const {
			return KeyboardGlobal::isDown(key);
		}
		bool isPressed(sf::Keyboard::Key key) const {
			return KeyboardGlobal::isPressed(key);
		}
	};


	class KeyboardInput : public Input {
	public:
		KeyboardInput();

		void update() override {}
		bool isDown(const InputButton key) const override;
		bool isPressed(const InputButton key) const override;

		_Input_Device(KeyboardInput);


	private:
		KeyboardHandle handle;
		std::map<InputButton, sf::Keyboard::Key> inputMap;
	};*/
}