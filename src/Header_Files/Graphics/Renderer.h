//Renderer.h

#pragma once
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include "SFML\Graphics.hpp"
#include "Texture.h"
#include "DrawableObject.h"
#include "DrawableObjTree.h"
#include "ActorUID.h"

namespace ic::gfx {

	struct RenderEvent;
	class DrawableObject;
	class RenderComponent;

	/**
	 * @brief                         The renderer class is the home of everything graphics related
     *                                it holds all the variables that the draw call requires
     *                                including what SFML's draw function needs
	 *
     *                                states gets set to RenderStates::Default and interpol gets updated at the beginning
     *                                of each draw call
     *
     *                                since SFML windows cannot live on multiple threads, so the window unfortunately must live here
     *                                this means the windowevent loop and keyboard polling must be done in this class
	*/
	class Renderer
	{
	public:

		/**
		 * @brief                     Constructor creates the SFML window and sets up the window with all its necessasry settings
		*/
		Renderer();
		~Renderer();

		/**
		 * @brief                     Polls all new RenderEvents and resets the state of the window for the next draw call
		 * @param interpol            The updated partial frame value to use for linear interpolation
		*/
		void preRender(const float interpol);

		/**
		 * @brief                     Draws every drawableTree in sequence using SFML draw calls
		*/
		void render();

		/**
		 * @brief                     Displays the window and performs any end of drawing maintainence
		*/
		void postRender();

		/**
		 * @brief                     As mentioned above the SFML window has to live on this thread, so I am storing it in this 
		 *                            class. Therefore the window update loop and input polling has to happen in this class.
		 *                            This is the function that does this.
		*/
		void updateInput();

		/**
		 * @brief                     Adds a RenderEvent to the current event queue, RenderEvents are how the rest of the game engine
		 *                            interacts with the graphics module, the event queue is polled and cleared before every draw call
		 * @param event               The event to be added to the queue
		*/
		void addEvent(std::unique_ptr<RenderEvent> event);

	private:

		friend class GfxTest;


		friend struct RenderEvent;
		friend class DrawableObject;
		friend class DrawableVertices;


		friend struct LoadTextureEvent;
		friend struct UnloadTextureEvent;

		template <typename T>
		friend struct CreateDrawableObjectEvent;
		friend struct AddDrawableTreeChildBackEvent;
		friend struct AddDrawableTreeChildFrontEvent;
		friend struct RemoveDrawableTreeChildEvent;


		/**
		 * @brief                     Loads a texture into renderer memory from a file
		 * @param texturename         The file name of the texture to load
		*/
		void loadTexture(const std::string& texturename);

		/**
		 * @brief                     Unloads a texture for when a texture is no longer in use 
		 * @param texturename         The file name of the texture to load
		*/
		void unloadTexture(const std::string& texturename);

		/**
		 * @brief                     Gets a texture from renderer memory based on its name
		 * @param texturename         The file name of the texture to get
		 * @return                    The texture associated with the texturename supplied
		*/
		Texture* getTexture(const std::string& texturename);

		/**
		 * @brief                     Creates a new drawable tree pointing to the supplied DrawableObject
		 *                            and links the new tree to the supplied ActorUID. The tree starts
		 *                            with no connections
		 * @param baseDrawable        The DrawableObject to use to create the tree
		 * @param actor               The ActorUID to link the created tree to
		*/
		void createDrawableTree(std::unique_ptr<DrawableObject> baseDrawable, const ActorUID& actor);

		/**
		 * @brief                     Adds one DrawableTree node as a front child of another.
		 *                            The front child is a child that draws on top of its parent
		 *                            The two trees to be connected is determined by their actor IDS
		 * @param parentID            The ActorUID of the parent in the new connection
		 * @param childID             The ActorUID of the child in the new connection
		*/
		void addDrawableTreeChildFront(const ActorUID parentID, const ActorUID childID);

		/**
		 * @brief                     Adds one DrawableTree node as a back child of another.
		 *                            The back child is a child that draws under its parent
		 *                            The two trees to be connected is determined by their actor IDS
		 * @param parentID            The ActorUID of the parent in the new connection
		 * @param childID             The ActorUID of the child in the new connection
		*/
		void addDrawableTreeChildBack(const ActorUID parentID, const ActorUID childID);
		
		/**
		 * @brief                     Makes the corresponding DrawableTree to the supplied ActorUID no
		 *                            longer a child of any other tree. Since a tree can only ever have
		 *                            1 parent at a time it is sufficient to only supply the child to
		 *                            the function
		 * @param childID             The ActorUID that is becomming independent again
		*/
		void removeDrawableTreeChild(const ActorUID childID);

		/**
		 * @brief                     Internal child adding function to reduce code duplication
		 * @param parentID            The ActorUID of the parent in the new connection
		 * @param childID             The ActorUID of the child in the new connection
		 * @param front               Whether the new connection is a front child or a back child
		*/
		void addDrawableTreeChild(const ic::ActorUID parentID, const ic::ActorUID childID, bool front);

		/**
		 * @brief                     Excecute every new event since the last time handleEvents() was called
		*/
		void handleEvents();

		/**
		 * @brief                     Gets the next event from the RenderEvent queue and stores it in the supplied pointer
		 * @param event               The pointer that the polled event will be stored in
		 * @return                    Returns true if an event was found, false otherwise
		*/
		bool pollEvent(std::unique_ptr<RenderEvent>& event);

		/**
		 * @brief                     Gets a pointer to the internal RenderWindow
		 *                            mostly for use with  SFML internal functions
		 * @return                    A raw pointer to the internal RenderWindow(which is a smart pointer normally)
		*/
		sf::RenderWindow* getWindow();

		/**
		 * @brief                     Internal variable that keeps track of the internal interpolation value
		 *                            for each frame. This interpolation value is the current subframe that
		 *                            the game is on when the pre draw function is called
		*/
		float interpol = 0.0f;

		/**
		 * @brief                     The SFML RenderStates value for calling SFML's draw function
		*/
		sf::RenderStates states = sf::RenderStates::Default;

		/**
		 * @brief                     The SFML RenderWindow 
		*/
		std::unique_ptr<sf::RenderWindow> window;

		/**
		 * @brief                     The texture cache, referenced by their file names
		*/
		std::map<std::string, std::shared_ptr<Texture>> textures;

		/**
		 * @brief                     Maps each DrawableTree to its corrosponding Actor through its ActorUID
		*/
		std::map<ic::ActorUID, std::shared_ptr<DrawableObjTree>> actorToTreeMap;

		/**
		 * @brief 		              Array of all the drawabletrees currently loaded and ready to be drawn
		*/
		std::vector<std::shared_ptr<DrawableObjTree>> drawableTrees;

		/**
		 * @brief                     The RenderEvent queue
		*/
		std::queue<std::unique_ptr<RenderEvent>> renderEventQueue;
	};
}

