#pragma once
#include "MenuButton.h"
#include "Scene.h"

namespace ic {
	

	class MainMenu : public Scene {
	public:
		MainMenu();
		void draw(const float interpol) override;
		void update() override;
		std::string getName() const override {
			return "MainMenuState";
		}
	private:
		std::vector<std::shared_ptr<MenuButton>> options;
	};

}