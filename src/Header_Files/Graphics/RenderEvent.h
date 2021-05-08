#pragma once
#include <string>
#include <memory>
#include "Renderer.h"
#include "DrawableObject.h"
#include "DrawableObjTree.h"

namespace ic::gfx {

	class DrawableObject;
	class Renderer;
	class RenderComponent;

	struct RenderEvent {
		RenderEvent() {}
		virtual ~RenderEvent() {}
		virtual void excecute(Renderer& renderer) const = 0;

		//void (*exceuctionFunction)(Renderer&);
	};

	struct LoadTextureEvent :  RenderEvent {
		LoadTextureEvent(const std::string& textureName);
		void excecute(Renderer& renderer) const override;
		std::string textureName;
	};

	struct UnloadTextureEvent : RenderEvent {
		UnloadTextureEvent(const std::string& textureName);
		void excecute(Renderer& renderer) const override;
		std::string textureName;
	};

	//creates a drawableobject and an accompanying tree in renderer memory attached to no other trees,
	//attached the supplied ActorUID to this object, do not allow two trees to be attached to the same ActorUID
	template <typename T>
	struct CreateDrawableObjectEvent : public RenderEvent {
		template<typename... Args>
		CreateDrawableObjectEvent(const ActorUID& actor, Args && ... args) : actor(actor), drawable(new T(std::forward<Args>(args)...)) {

		}


		void excecute(Renderer& renderer) const override {
				renderer.createDrawableTree(std::unique_ptr<DrawableObject>(drawable), actor);
		}

		ActorUID actor;
		DrawableObject* drawable;
	};

	struct AddDrawableTreeChildBackEvent : public RenderEvent {
		AddDrawableTreeChildBackEvent(ActorUID parentID, ActorUID childID) : parentID(parentID), childID(childID) {

		}

		void excecute(Renderer& renderer) const override {
			renderer.addDrawableTreeChildBack(parentID, childID);
		}

		ActorUID parentID;
		ActorUID childID;
	};

	struct AddDrawableTreeChildFrontEvent : public RenderEvent {
		AddDrawableTreeChildFrontEvent(ActorUID parentID, ActorUID childID) : parentID(parentID), childID(childID) {

		}

		void excecute(Renderer& renderer) const override {
			renderer.addDrawableTreeChildFront(parentID, childID);
		}

		ActorUID parentID;
		ActorUID childID;
	};

	struct RemoveDrawableTreeChildEvent : public RenderEvent {
		RemoveDrawableTreeChildEvent(ActorUID childID) : childID(childID) {

		}

		virtual void excecute(Renderer& renderer) const override {
			renderer.removeDrawableTreeChild(childID);
		}

		ActorUID childID;
	};
}
