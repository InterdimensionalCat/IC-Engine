#pragma once
#include "Input.h"
#include "GameInput.h"

namespace ic {

	class Port;

	class BoopAI :
		public GameInputDevice
	{
	public:

		void update() override;
		bool isDown(const GameInputButton key) const override;
		bool isPressed(const GameInputButton key) const override;

		void pressKey(const GameInputButton key);
		void releaseKey(const GameInputButton key);

	private:
		BoopAI(const std::shared_ptr<Port> port);
		KeyListener<GameInputButton> keylistener;

	};
}

