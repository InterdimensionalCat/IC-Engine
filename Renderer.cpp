#include "include.h"
#include "Renderer.h"


Renderer::Renderer(Game* in) : instance(in) {

}

Renderer::~Renderer() {

}

WindowData* Renderer::getWindowData() {
	return instance->MainWindow;
}

WindowData* Renderer::getWindowData(const std::string &subwindowname) {
	if (instance->subwindows.find(subwindowname) != instance->subwindows.end()) {
		return instance->subwindows.at(subwindowname).get();
	}
	else {
		cout << "Window not found!\n";
		return instance->MainWindow;
	}
}
