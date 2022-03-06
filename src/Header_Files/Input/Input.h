#pragma once
#include "InputDevice.h"

namespace ic {

	class InputDevice;

	class Input {
	public:
		static Input* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<Input>();
			}
			return instance.get();
		}

		void update() {
			for (auto& device : inputDevices) {
				device->update();
			}
		}

	private:
		Input() {}
		inline static std::unique_ptr<Input> instance;
		std::vector<std::shared_ptr<InputDevice>> inputDevices;
	};

	template<typename KeyType>
	class KeyListener {
	public:
		bool isDown(KeyType key) const {
			return hkeys.find((int)key) != hkeys.end();
		}

		bool isPressed(KeyType key) const {
			return pkeys.find((int)key) != pkeys.end();
		}

		void update() {
			pkeys.clear();
		}

		void pressKey(const KeyType key) {
			pkeys.emplace((int)key, key);
			hkeys.emplace((int)key, key);
		}

		void releaseKey(const KeyType key) {
			hkeys.erase((int)key);
		}
	private:
		std::map<int, KeyType> pkeys = std::map<int, KeyType>();
		std::map<int, KeyType> hkeys = std::map<int, KeyType>();
	};
}
