#pragma once
#pragma once
#include "Texture.h"

namespace ic {
	class Window;

	/**
	 * @brief struct that contains all the parameters to construct an animation
	 * @details is also convertable to and from json in order to be easily used 
	 * in components
	*/
	struct AnimationEntry {
		std::string  filename;
		sf::Vector2i frameDim;
		sf::Vector2f targetDim;
		int          firstFrame;
		int          numFrames;
		int          fps;

		void toJson(std::shared_ptr<json> file) const {
			(*file)["filename"] = filename;
			(*file)["frameDim"]["x"] = frameDim.x;
			(*file)["frameDim"]["y"] = frameDim.y;
			(*file)["targetDim"]["x"] = targetDim.x;
			(*file)["targetDim"]["y"] = targetDim.y;
			(*file)["firstFrame"] = firstFrame;
			(*file)["numFrames"] = numFrames;
			(*file)["fps"] = fps;
		}

		void fromJson(const std::shared_ptr<json>& file) {
			filename = (*file)["filename"];
			frameDim.x = (*file)["frameDim"]["x"];
			frameDim.y = (*file)["frameDim"]["y"];
			targetDim.x = (*file)["targetDim"]["x"];
			targetDim.y = (*file)["targetDim"]["y"];
			firstFrame = (*file)["firstFrame"];
			numFrames = (*file)["numFrames"];
			fps = (*file)["fps"];
		}

		void toJson(json& file) const {
			file["filename"] = filename;
			file["frameDim"]["x"] = frameDim.x;
			file["frameDim"]["y"] = frameDim.y;
			file["targetDim"]["x"] = targetDim.x;
			file["targetDim"]["y"] = targetDim.y;
			file["firstFrame"] = firstFrame;
			file["numFrames"] = numFrames;
			file["fps"] = fps;
		}

		void fromJson(const json& file) {
			filename = file["filename"];
			frameDim.x = file["frameDim"]["x"];
			frameDim.y = file["frameDim"]["y"];
			targetDim.x = file["targetDim"]["x"];
			targetDim.y = file["targetDim"]["y"];
			firstFrame = file["firstFrame"];
			numFrames = file["numFrames"];
			fps = file["fps"];
		}
	};

	/**
	 * @brief class representing a 2 dimensional sprite based animation
	 * @details contains small animations loaded from a spritemap in a left-right up-down sequence;
	 * EX.png:
	 * 
	 *           ________________________
	 *          | frame1 2       3     4 |
	 *          | 5      6       7     8 |
	 *          | etc...                 |
	 *          |________________________|
	 * 
	 * 
	 * Animation length is limited by type of graphics card. I dont know how to get max texture size supported for a graphics card,
	 * but for sure anything larger than 8192 in either direction is too large, this may eventually limit the duration of animations
	 * but with the above restriction almost 9 seconds of fairly high resolution sprite animation (500x500px) which is quite a long
	 * time for a single animation, and if it ever becomes a problem I can probably rewrite it so that animations can be daisy chained
	 * together like a linked list
	*/
	class Animation
	{
	public:
		/*
		Params:
		frameDim: dimension of each frame on the texture
		targetDim: dimension of each frame to be output in the window
		numFrames: the number of frames in the animation
		offset: a small visual translation that moves
		this animation away from the center whenever this frame is drawn
		*/

		/**
		 * @brief constructs an animation with the given parameters
		 * @param filename the name of the animation file
		 * @param frameDim dimension of each frame on the texture
		 * @param targetDim dimension of each frame to be output in the window
		 * @param firstFrame the index of the first frame for this animation
		 * @param numFrames the number of frames in the animation
		 * @param fps the frames per second to run this frame at
		 * @param flip whether or not to construct this animation flipped or not
		*/
		Animation(const std::string& filename, const sf::Vector2i& frameDim, const sf::Vector2f& targetDim, const int firstFrame, const int numFrames, const int fps, const bool flip = false);

		/**
		 * @brief constructs an animation with the parameters inside the supplied AnimationEntry
		 * @param entry the entry to construct from
		 * @param flip whether or not to construct this animation flipped or not
		*/
		Animation(const AnimationEntry& entry, const bool flip = false);

		/**
		 * @brief convert the params in this animation to an AnimationEntry
		 * @return the created AnimationEntry
		*/
		AnimationEntry getAnimEntry() {
			return AnimationEntry(name, frameDim, targetDim, firstFrame, numFrames, framerate);
		}


		//top left corner

		/**
		 * @brief set the position on the screen to draw this animation at
		 * @param posInPixels the top left corner position to set the animation to, in pixels
		*/
		void setPosition(const sf::Vector2f& posInPixels);

		/**
		 * @brief updates the animation's current frame counter
		*/
		void update();

		/**
		 * @brief draw the animation to the screen
		 * @param window the window to draw the animation to
		*/
		void draw(Window& window);

		/**
		 * @brief changes the frame to draw to the screen to the next frame in the list
		*/
		void advanceFrame();

		/**
		 * @brief returns the file name of this animation
		 * @return the file name
		*/
		std::string getName() const { return name; };

		/**
		 * @brief sets the animation flipped or not flipped based on the supplied bool
		 * @param flip whether or not to flip the animation
		*/
		void setFlipped(const bool flip);

		/**
		 * @brief is the animation flipped or not
		 * @return true if the animation is currently flipped
		*/
		bool isFlipped() const {
			return flip;
		}

		/**
		 * @brief returns the dimensions of this animation when drawn to the screen
		 * @return the target dimensions
		*/
		sf::Vector2f getDimensions() const {
			return targetDim;
		}

		/**
		 * @brief resets the animation back to the beginning
		*/
		void reset();

	private:

		/**
		 * @brief see params list above
		*/
		sf::Sprite frame;

		Texture tex;
		int framerate;
		int frameNum;
		int numFrames;
		int firstFrame;
		int framesPerRow;
		std::string name;
		sf::Vector2i frameDim;
		sf::Vector2f targetDim;

		int framesTillNext;
		int activeFrames;
		bool flip = false;
	};
}

