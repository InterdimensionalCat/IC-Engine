#include "include.h"
#include "Animation.h"
#include "GameTransform.h"
#include "Animator.h"



//params: fdim = dimension of 1 frame on the texture, tdim = dimension 1 frame to output
Animation::Animation(const sf::Vector2i& frameDim, const s2d::PixelUnits::Dimension& targetDim, const std::string& filename, const int numFrames) :
frameDim(frameDim), targetDim(targetDim.toSFMLVec<float>()), name(filename), numFrames(numFrames) {

	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "animations";
	filepath /= filename;
	filepath += ".png";	

	if (!tex.loadFromFile(filepath.string())) {
#ifdef _DEBUG
		throw TextureLoadException(filename, filepath.string());
#endif
	}

	frame.setTexture(tex);
	frame.setTextureRect(IntRect(0, 0, frameDim.x, frameDim.y));
	frame.setScale(Vector2f(this->targetDim.x / (float)frameDim.x, this->targetDim.y / (float)frameDim.y));

	framerate = 30;
	frameNum = 0;

#ifdef _DEBUG
	auto test = (int)tex.getSize().x / frameDim.x * (int)tex.getSize().y / frameDim.y;
	assert(numFrames <= test);
#endif
	framesPerRow = tex.getSize().x / frameDim.x;
	activeFrames = (int)instance->targetFPS / framerate;
	framesTillNext = activeFrames;

}


void Animation::setFlipped(bool flip) {

	Animation::flip = flip;

	if (flip) {
		Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(-frameDim.x, frameDim.y)));
	}
	else {
		Vector2i frameTopLeft((frameNum % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(frameDim.x, frameDim.y)));
	}
}

void Animation::reset() {
	frameNum = 0;
	framesTillNext = 0;
	setFlipped(false);
}


void Animation::draw(Renderer* renderer) {

	auto states = renderer->states;
	auto target = renderer->window.get();

	if (--framesTillNext <= 0) {
		advanceFrame();
		framesTillNext = activeFrames;
	}

	//interpolate frame
	frame.setOrigin(lerp(((s2d::PixelUnits::Point)parent->transform->getPrevPos()).toSFMLVec<float>() - targetDim / 2.0f, 
		((s2d::PixelUnits::Point)parent->transform->getPos()).toSFMLVec<float>() - targetDim / 2.0f, renderer->interpol));

	frame.setPosition(lerp(((s2d::PixelUnits::Point)parent->transform->getPrevPos()).toSFMLVec<float>(),
		((s2d::PixelUnits::Point)parent->transform->getPos()).toSFMLVec<float>(), renderer->interpol));

	target->draw(frame, states);

}

void Animation::advanceFrame() {
	frameNum = (frameNum + 1) % numFrames;

	if (flip) {
		Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(-frameDim.x, frameDim.y)));
	}
	else {
		Vector2i frameTopLeft((frameNum % framesPerRow) * frameDim.x, (frameNum / framesPerRow) * frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(frameDim.x, frameDim.y)));
	}
}