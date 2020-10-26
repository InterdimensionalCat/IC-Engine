#pragma once

class GameTransform;

class Animation
{
public:
	Animation() {

	}

	void init(const Vector2f &fdim, const Vector2f &tdim, const string &filename);

	void draw(sf::RenderTarget& target, sf::RenderStates states, const GameTransform* trans);
	void advanceFrame();
	string getName() { return name; };
	void setFlipped(bool flip);
	void reset() {
		frameNum = 0;
		framesTillNext = 0;
		setFlipped(false);
	}


	Sprite frame;

	Texture tex;
	int framerate;
	int frameNum;
	int numFrames;
	int framesPerRow;
	string name;
	Vector2f frameDim;
	Vector2f targetDim;

	int framesTillNext;
	int activeFrames;
	bool flip = false;
};

