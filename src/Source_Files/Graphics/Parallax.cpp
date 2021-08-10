#include "include.h"
#include "Parallax.h"
#include "Window.h"
#include "Camera.h"

using namespace ic;

Parallax::Parallax(const std::string& basename, const float baseX, const float baseY, const float growthX, const float growthY) {
	int bgCounter = 1;
	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "textures";

	while (fs::exists(filepath / (basename + "_" + std::to_string(bgCounter) + ".png"))) {
		layers.push_back(ParallaxLayer(
			basename + "_" + std::to_string(bgCounter)
			, baseX + (float)bgCounter * growthX, 
			baseY + (float)bgCounter * growthY));
		bgCounter++;
	}
}

Parallax::ParallaxLayer::ParallaxLayer(const std::string& texture, const float repetitionPercentX, const float repetitionPercentY) :
	tex(Texture(texture)), repetitionPercentX(repetitionPercentX), repetitionPercentY(repetitionPercentY) {
	tex.getTexture().setRepeated(true);
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i((int)Settings::getWidth(), (int)Settings::getHeight())));
	sprite.setTexture(tex.getTexture());
	//repetitionPercentX = tex.getTexture().getSize().x / toPixels(data.levelWidth);
}
void Parallax::ParallaxLayer::move(Camera& camera, const float percentX, const float percentY) {
	auto prevrect = sprite.getTextureRect();
	if (repetitionPercentY >= 1.0f) {
		prevrect.left = (int)(percentX * (repetitionPercentX * (float)tex.getTexture().getSize().x - Settings::getWidth()));
	}
	else {
		prevrect.left = (int)(percentX * (repetitionPercentX * (float)tex.getTexture().getSize().x - Settings::getWidth() * 0.0f));
	}

	if (repetitionPercentY >= 1.0f) {
		prevrect.top = (int)(percentY * (repetitionPercentY * (float)tex.getTexture().getSize().y - Settings::getHeight()));
	}
	else {
		prevrect.top = (int)(percentY * (repetitionPercentY * (float)tex.getTexture().getSize().y - Settings::getHeight() * 0.0f));
	}




	sprite.setTextureRect(prevrect);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.move(camera.scrollpos);
}
void Parallax::ParallaxLayer::draw(Window& window) const {
	window.window->draw(sprite, window.states);
}

void Parallax::move(Camera& camera) {

	//calc scroll here xd

	float percentX = 0;
	float percentY = 0;

	if (camera.boundsInPixels.x != (float)Settings::getWidth()) {
		percentX = camera.scrollpos.x / (camera.boundsInPixels.x - Settings::getWidth());
	}

	if (camera.boundsInPixels.y != Settings::getHeight()) {
		percentY = camera.scrollpos.y / (camera.boundsInPixels.y - Settings::getHeight());
	}

	//if (percentX != 0.0f || percentY != 0.0f) {
	for (auto& layer : layers) {
		layer.move(camera, percentX, percentY);
	}
	//}
}

void Parallax::draw(Window& window) const {
	for (auto& layer : layers) {
		layer.draw(window);
	}
}