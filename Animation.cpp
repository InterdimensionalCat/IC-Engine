#include "include.h"
#include "Animation.h"
#include "GameTransform.h"



//currently texture must be of the form n*a x b where n is the number of animation frames
void Animation::init(const Vector2f &fdim, const Vector2f &tdim, const string &filename) {

	frameDim = fdim;
	targetDim = tdim;
	name = filename;

	fs::path filepath(fs::current_path());
	filepath /= "animations";
	filepath /= filename;
	filepath += ".png";

	//cout << filepath.extension() << "\n";
	//cout << filepath.filename() << "\n";
	//cout << filepath.relative_path() << "\n";
	

	if (!tex.loadFromFile(filepath.generic_u8string())) {
		throw TextureLoadException(filename, filepath.generic_u8string());
	}

	frame.setTexture(tex);
	frame.setTextureRect(IntRect(0, 0, frameDim.x, frameDim.y));
	frame.setScale(Vector2f(targetDim.x / frameDim.x, targetDim.y / frameDim.y));

	framerate = 30;
	frameNum = 0;
	numFrames = tex.getSize().x / frameDim.x;
	activeFrames = instance->targetFPS / framerate;
	framesTillNext = activeFrames;

}


void Animation::setFlipped(bool flip) {
	//frame.setScale(-frame.getScale().x, frame.getScale().y);

	Animation::flip = flip;

	if (flip) {
		frame.setTextureRect(IntRect((frameNum + 1) * frameDim.x, 0, -frameDim.x, frameDim.y));
	}
	else {
		frame.setTextureRect(IntRect(frameNum * frameDim.x, 0, frameDim.x, frameDim.y));
	}
}


void Animation::draw(sf::RenderTarget& target, sf::RenderStates states, const GameTransform* trans) {
	if (--framesTillNext <= 0) {
		advanceFrame();
		framesTillNext = activeFrames;
	}

	//interpolate frame
	frame.setPosition(lerp(trans->getPrevPos() - targetDim / 2.0f, trans->getPos() - targetDim / 2.0f, instance->renderer->interpol));

	target.draw(frame, states);

}

void Animation::advanceFrame() {
	frameNum = (frameNum + 1) % numFrames;
	if (flip) {
		frame.setTextureRect(IntRect((frameNum + 1) * frameDim.x, 0, -frameDim.x, frameDim.y));
	}
	else {
		frame.setTextureRect(IntRect(frameNum * frameDim.x, 0, frameDim.x, frameDim.y));
	}
}