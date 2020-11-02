#pragma once

class GameTransform;
class Animator;

class Animation
{
public:
	Animation(const sf::Vector2i& frameDim, const s2d::PixelUnits::Dimension& targetDim, const std::string& filename, const int numFrames);

	void draw(Renderer* renderer);
	void advanceFrame();

	string getName() const { return name; };
	void setFlipped(const bool flip);
	void reset();


	sf::Sprite frame;

	Texture tex;
	int framerate;
	int frameNum;
	int numFrames;
	int framesPerRow;
	std::string name;
	sf::Vector2i frameDim;
	sf::Vector2f targetDim;

	int framesTillNext;
	int activeFrames;
	bool flip = false;

	Animator* parent;
};

