#pragma once

namespace ic {
	class InputDevice {
	public:
		InputDevice() {}
		virtual void update() = 0;
		virtual std::string getName() const = 0;
	};

	class KeyboardInput : public InputDevice {
		KeyboardInput() {}
		void update() override {

		}

		std::string getName() const override {
			return "KeyboardInput";
		}
	};
}