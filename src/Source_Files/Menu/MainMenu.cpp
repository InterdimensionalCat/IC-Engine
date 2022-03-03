#include "include.h"
#include "MainMenu.h"
#include "ImGui/imgui.h"
#include "Renderer.h"
#include "Window.h"
#include "AudioEngine.h"
#include "MenuButton.h"
#include "SceneManagement.h"
#include "Scene.h"
#include "WindowEventListener.h"

using namespace ic;

MainMenu::MainMenu() {
	void (*callback_fn)(std::string) =
		SceneManager::changeSceneStatic;
	options.push_back(std::make_shared<MenuButton>(s2d::Vec2p(100, 100), "Game",
		callback_fn,
		std::string("GameScene")));
	std::shared_ptr<WindowEventListener> base;
	base = std::static_pointer_cast<WindowEventListener>(options.front());
	Renderer::get()->window->registerWindowEventListener(base);
}

void MainMenu::draw(const float interpol) {

	Renderer::get()->window->preRender(interpol);

	for (auto& option : options) {
		option->draw(interpol);
	}

	//try {
	//	//ImGui::NewFrame();
	//	ImGui::BeginMainMenuBar();
	//	ImGui::MenuItem("Test", "A", false);
	//	ImGui::Button("Look at this pretty button");
	//	ImGui::EndMainMenuBar();
	//	//ImGui::End();
	//	//ImGui::EndFrame();
	//}
	//catch (std::exception e) {
	//	Logger::error("Error rendering Imgui: {}", e.what());
	//	throw std::exception();
	//}
	Renderer::get()->window->renderGui();
	Renderer::get()->window->postRender();
}

void MainMenu::update() {
	AudioEngine::get()->update();

	if (!Renderer::get()->window->updateInput()) {
		Settings::setRunning(false);
		return;
	}
}