#pragma once
#include <vector>
#include <memory>
#include "DrawableObject.h"
#include "ActorUID.h"
#include <optional>


namespace ic::gfx {
	/**
	 * @brief                         Tree and Node class for drawable object heirarchies. This allows for different
	 *                                drawable objects that are not necessasarily related in other ways to move reletive
	 *                                to eachother, such as a player holding a gun
	 * 
	 *                                each actor has 1 and only 1 DrawableObjectTree associated with it
	*/
	class DrawableObjTree {
	public:

		/**
		 * @brief                     Constructs a DrawableObjTree with no children                    
		 * @param drawable            The DrawableObject represented by the tree
		 * @param actor               The ActorUID associated with this tree
		*/
		DrawableObjTree(std::unique_ptr<DrawableObject> drawable, const ic::ActorUID actor);

		/**
		 * @brief                     Removes the supplied child from this tree's list of children
		 * @param childBase           The child tree to remove
		*/
		void removeChild(std::shared_ptr<DrawableObjTree> childBase);

		/**
		 * @brief                     Adds the supplied tree as a back child to this tree
		 * @param childBase           The tree to add as a back child
		*/
		void addBackChild(std::shared_ptr<DrawableObjTree> childBase);

		/**
		 * @brief                     Adds the supplied tree as a front child to this tree
		 * @param childBase           The tree to add as a front child
		*/
		void addFrontChild(std::shared_ptr<DrawableObjTree> childBase);

		/**
		 * @brief                     Draws the internal DrawableObject at this node, and
		 *                            draws down the tree, draws front children on top of
		 *                            this node and back children behind it, every child
		 *                            uses its reletive origin, blend mode, and other
		 *                            renderstates variables as the states variable passed
		 *                            in plus this objects' state modification
		 * @param renderer            The global renderer object to actually do the drawing
		 * @param states              The current state of the tree drawing before this node's
		 *                            states are added
		*/
		void draw(Renderer& renderer, sf::RenderStates states);

		/**
		 * @brief                     The drawable object that this node in the tree will draw
		*/
		std::unique_ptr<DrawableObject> drawable;

		/**
		 * @brief                     This node's front children
		*/
		std::vector<std::shared_ptr<DrawableObjTree>> frontchildren;

		/**
		 * @brief                     This node's back children
		*/
		std::vector<std::shared_ptr<DrawableObjTree>> backchildren;

		//potential alternative

		//std::vector<std::shared_ptr<DrawableObjTree>> children;
		//bool isFront;

		/**
		 * @brief                     The actor associated with this drawable node
		 *                            represented by its ActorUID
		*/
		ic::ActorUID actor;

		/**
		 * @brief                     The ActorUID of the parent of this node, if
		 *                            a parent exists
		*/
		std::optional<ic::ActorUID> parent;
	};
}