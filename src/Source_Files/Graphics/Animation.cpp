#include "include.h"
#include "Animation.h"
#include "Window.h"

using namespace ic;


//params: fdim = dimension of 1 frame on the texture, tdim = dimension 1 frame to output
Animation::Animation(const std::string& filename, const sf::Vector2i& frameDim, const sf::Vector2f& targetDim, const int firstFrame, const int numFrames, const int fps, const bool flip) : name(filename), tex(Texture(filename)), 
	frameDim(frameDim), targetDim(targetDim), firstFrame(firstFrame), numFrames(numFrames), framerate(fps) {

	tex.getTexture().setRepeated(true);

	frame.setTexture(tex.getTexture());
	frame.setTextureRect(sf::IntRect(0, 0, frameDim.x, frameDim.y));
	frame.setScale(sf::Vector2f(this->targetDim.x / (float)frameDim.x, this->targetDim.y / (float)frameDim.y));

	frameNum = firstFrame;

#ifdef _DEBUG
	auto test = (int)tex.getTexture().getSize().x / frameDim.x * (int)tex.getTexture().getSize().y / frameDim.y;
	assert(numFrames <= test);
#endif
	framesPerRow = tex.getTexture().getSize().x / frameDim.x;
	activeFrames = (int)Settings::getTargetFPS() / framerate;
	framesTillNext = activeFrames;

	setFlipped(flip);
}

Animation::Animation(const AnimationEntry& entry, const bool flip) : Animation(entry.filename, entry.frameDim, entry.targetDim, entry.firstFrame, entry.numFrames, entry.fps, flip) {}

void Animation::setPosition(const sf::Vector2f& posInPixels) {
	frame.setPosition(round(posInPixels.x), round(posInPixels.y));
}

void Animation::setFlipped(bool flip) {

	Animation::flip = flip;

	if (flip) {
		sf::Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(sf::IntRect(frameTopLeft, sf::Vector2i(-frameDim.x, frameDim.y)));
	}
	else {
		sf::Vector2i frameTopLeft((frameNum % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(sf::IntRect(frameTopLeft, sf::Vector2i(frameDim.x, frameDim.y)));
	}
}

void Animation::reset() {
	frameNum = firstFrame;
	framesTillNext = 0;
	setFlipped(false);
}


void Animation::update() {
	if (--framesTillNext <= 0) {
		advanceFrame();
		framesTillNext = activeFrames;
	}
}

void Animation::draw(Window& window) {
	auto states = window.states;
	window.window->draw(frame, states);
}

void Animation::advanceFrame() {
	frameNum = (frameNum + 1);
	if (frameNum == (numFrames + firstFrame)) {
		frameNum = firstFrame;
	}

	if (flip) {
		sf::Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(sf::IntRect(frameTopLeft, sf::Vector2i(-frameDim.x, frameDim.y)));
	}
	else {
		sf::Vector2i frameTopLeft((frameNum % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(sf::IntRect(frameTopLeft, sf::Vector2i(frameDim.x, frameDim.y)));
	}
}
