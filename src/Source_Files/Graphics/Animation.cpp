#include "include.h"
#include "Animation.h"
#include "GameTransform.h"



//params: fdim = dimension of 1 frame on the texture, tdim = dimension 1 frame to output
void Animation::init(const Vector2f &fdim, const Vector2f &tdim, const string &filename, const int numFrames) {

	frameDim = fdim;
	targetDim = tdim; 
	name = filename; 
	Animation::numFrames = numFrames;

	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "animations";
	filepath /= filename;
	filepath += ".png";

	//cout << filepath.extension() << "\n";
	//cout << filepath.filename() << "\n";
	//cout << filepath.relative_path() << "\n";
	

	if (!tex.loadFromFile(filepath.generic_u8string())) {
#ifdef _DEBUG
		throw TextureLoadException(filename, filepath.generic_u8string());
#endif
	}

	frame.setTexture(tex);
	frame.setTextureRect(IntRect(0, 0, frameDim.x, frameDim.y));
	frame.setScale(Vector2f(targetDim.x / frameDim.x, targetDim.y / frameDim.y));

	framerate = 30;
	frameNum = 0;
	//numFrames = tex.getSize().x / (int)frameDim.x + tex.getSize().y / (int)frameDim.y;
#ifdef _DEBUG
	auto test = tex.getSize().x / (int)frameDim.x * tex.getSize().y / (int)frameDim.y;
	assert(numFrames <= test);
#endif
	framesPerRow = tex.getSize().x / (int)frameDim.x;
	activeFrames = instance->targetFPS / framerate;
	framesTillNext = activeFrames;

}


void Animation::setFlipped(bool flip) {
	//frame.setScale(-frame.getScale().x, frame.getScale().y);

	Animation::flip = flip;

	if (flip) {
		Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * (int)frameDim.x, (frameNum / framesPerRow) * (int)frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(-(int)frameDim.x, (int)frameDim.y)));
	}
	else {
		Vector2i frameTopLeft((frameNum % framesPerRow) * (int)frameDim.x, (frameNum / framesPerRow) * (int)frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i((int)frameDim.x, (int)frameDim.y)));
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
		Vector2i frameTopLeft(((frameNum + 1) % framesPerRow) * (int)frameDim.x, (frameNum / framesPerRow) * (int)frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i(-(int)frameDim.x, (int)frameDim.y)));
	}
	else {
		Vector2i frameTopLeft((frameNum % framesPerRow) * (int)frameDim.x, (frameNum / framesPerRow) * (int)frameDim.y);
		frame.setTextureRect(IntRect(frameTopLeft, Vector2i((int)frameDim.x, (int)frameDim.y)));
	}
}