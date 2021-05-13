#pragma once
#include <string>
#include <memory>
#include "Renderer.h"
#include "DrawableObject.h"
#include "DrawableObjTree.h"


//need to move implementations outside of the header file

namespace ic::gfx {

	class DrawableObject;
	class Renderer;
	class RenderComponent;

	/**
	 * @brief                         The RenderEvent class is how literally everything outside of the Renderer
	 *                                module interacts with it. Therefore any action that an outside module would want
	 *                                to do to the renderer must have an even that allows it to do that without giving
	 *                                the sender direct access to anything within the graphics module, a good way to know that
	 *                                this is achieved is that classes outside the graphics module should never use anything
	 *                                with the ic::gfx namespace except for RenderEvents themselves
	*/
	struct RenderEvent {

		/**
		 * @brief                     Constructor
		*/
		RenderEvent() {}
		/**
		 * @brief                     Events are noncopyable
		 * @param other 
		*/
		RenderEvent(const RenderEvent&) = delete;

		/**
		 * @brief                     Events are noncopyable
		 * @param other 
		 * @return 
		*/
		RenderEvent& operator=(const RenderEvent& rhs) = delete;

		virtual ~RenderEvent() {}

		/**
		 * @brief                     This is the function that the renderer calls when the event is polled, note that since
		 *                            This is implimented inside the RenderEvent class itself a sender can create and send
		 *                            an event without ever being aware of the underlying renderer interface, furthermore changes
		 *                            in how the renderer works is unlikely to require how these events are used, so both sides are
		 *                            decoupled and resistant to change
		 * @param renderer 
		*/
		virtual void excecute(Renderer& renderer) const = 0;

		//void (*exceuctionFunction)(Renderer&);
	};

	/**
	 * @brief                         Event that loads a texture into renderer memory
	*/
	struct LoadTextureEvent :  RenderEvent {

		/**
		 * @brief                     Constructs an event with the supplied texture name
		 * @param textureName         The file name of the texture to load
		*/
		LoadTextureEvent(const std::string& textureName);

		/**
		 * @brief                     Excecution function
		 * @param renderer            Renderer instance
		*/
		void excecute(Renderer& renderer) const override;

		/**
		 * @brief                     Texture name needs to be stored for when the
		 *                            renderer actually handles the event
		*/
		std::string textureName;
	};

	/**
	 * @brief                         Event that unloads a texture from renderer memory
	*/
	struct UnloadTextureEvent : RenderEvent {

		/**
		 * @brief                     Constructs the event with the supplied texture name
		 * @param textureName         The file name of the texture to unload
		*/
		UnloadTextureEvent(const std::string& textureName);

		/**
		 * @brief                     Excecution function
		 * @param renderer            Supplied renderer
		*/
		void excecute(Renderer& renderer) const override;

		/**
		 * @brief                     The file name of the texture to unload
		*/
		std::string textureName;
	};

	/**
	 * @brief                         Event that creates a drawableobject and an accompanying tree 
	 *                                in renderer memory attached to no other trees attached to the
	 *                                supplied ActorUID
	 * @tparam T                      The type of the class of the DrawableObject created, must actually be a
	 *                                subclass of DrawableObject
	*/
	template <typename T>
	struct CreateDrawableObjectEvent : public RenderEvent {

		/**
		 * @brief                     A raw pointer to the DrawableObject is created on construction and the
		 *                            ActorUID is stored. You supply the arguments to any valid constructor of the
		 *                            object T and that constructor will be called to construct the DrawableObject
		 *                            (works like std::make_unique/std::make_shared)
		 * @tparam ...Args            These are automatically determined using CTAD, they are the types of the
		 *                            parameters of the constructor you are attempting to call for the DrawableObject
		 * @param actor               The ActorUID to be bound to this DrawableObject and DrawableTree
		 * @param ...args             The variadic arguments to pass in. These arguments should match the expected input
		 *                            for a corresponding constructor of T
		 * 
		 * @TODO:                     Need to make this less memory leak prone/need to rule of 5 this
		*/
		template<typename... Args>
		CreateDrawableObjectEvent(const ActorUID& actor, Args && ... args) : actor(actor), drawable(new T(std::forward<Args>(args)...)) {

		}

		~CreateDrawableObjectEvent() {
			//manual dynamic memory means delete calls
			delete drawable;
		}

		/**
		 * @brief                     Excecute function
		 * @param renderer            Supplied renderer
		*/
		void excecute(Renderer& renderer) const override {

			//swap the pointer out and null it so that destructor doesn't
			//delete the unique pointer's contents by accident
			auto* temp = drawable;
			drawable = nullptr;

			renderer.createDrawableTree(std::unique_ptr<DrawableObject>(temp), actor);
		}

		/**
		 * @brief                     The ActorUID of the actor associated with this
		 *                            DrawableObject and Tree
		*/
		ActorUID actor;

		/**
		 * @brief                     The DrawableObject constructed at Event creation
		*/
		DrawableObject* drawable;
	};

	/**
	 * @brief                         Adds the DrawableTree associated with childID as a back child of
	 *                                the DrawableTree associated with parentID in renderer memory
	*/
	struct AddDrawableTreeChildBackEvent : public RenderEvent {

		/**
		 * @brief                     Constructs the event with the given ActorUIDs as the parent and child
		 *                            to link
		 * @param parentID            The ActorUID of the new parent
		 * @param childID             The ActorUID of the new child
		*/
		AddDrawableTreeChildBackEvent(ActorUID parentID, ActorUID childID) : parentID(parentID), childID(childID) {

		}

		/**
		 * @brief                     Excecution function
		 * @param renderer            Supplied renderer
		*/
		void excecute(Renderer& renderer) const override {
			renderer.addDrawableTreeChildBack(parentID, childID);
		}


		/**
		 * @brief                     ActorUID of the new parent
		*/
		ActorUID parentID;

		/**
		 * @brief                     ActorUID of the new child
		*/
		ActorUID childID;
	};

	/**
	 * @brief                         Adds the DrawableTree associated with childID as a front child of
	 *                                the DrawableTree associated with parentID in renderer memory
	*/
	struct AddDrawableTreeChildFrontEvent : public RenderEvent {

		/**
		 * @brief                     Constructs the event with the given ActorUIDs as the parent and child
		 *                            to link
		 * @param parentID            The ActorUID of the new parent
		 * @param childID             The ActorUID of the new child
		*/
		AddDrawableTreeChildFrontEvent(ActorUID parentID, ActorUID childID) : parentID(parentID), childID(childID) {

		}

		/**
		 * @brief                     Excecution function
		 * @param renderer            Supplied renderer
		*/
		void excecute(Renderer& renderer) const override {
			renderer.addDrawableTreeChildFront(parentID, childID);
		}

		/**
		 * @brief                     ActorUID of the new parent
		*/
		ActorUID parentID;

		/**
		 * @brief                     ActorUID of the new child
		*/
		ActorUID childID;
	};

	/**
	 * @brief                         Destroys any link between the tree associated with the supplied
	 *                                ActorUID and a parent. The parent does not need to be known by
	 *                                this function (this might not be good design)
	*/
	struct RemoveDrawableTreeChildEvent : public RenderEvent {

		/**
		 * @brief                     Constructs the event with the supplied child ActorUID
		 * @param childID             The ActorUID of the child to remove parents from
		*/
		RemoveDrawableTreeChildEvent(ActorUID childID) : childID(childID) {

		}


		/**
		 * @brief                     Excecution function
		 * @param renderer            Supplied renderer
		*/
		virtual void excecute(Renderer& renderer) const override {
			renderer.removeDrawableTreeChild(childID);
		}

		/**
		 * @brief                     The child to remove parents from
		*/
		ActorUID childID;
	};
}
