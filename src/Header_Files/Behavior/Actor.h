#pragma once
#include <vector>
#include "Behavior.h"
#include <memory>
#include <string>

//Actor.h
/*
  The objects that make up the levels; functionally the same as unity's GameObject,
  can add descrete behaviors to game objects so that multiple objects can share 
  similar qualities without code duplication
*/

class Level;

class Actor
{
public:
	virtual ~Actor() {}

	//called before the first tick call, be very careful about the order in which behaviors start,
	//as behaviors set up their pointers to other behaviors on start call
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);

	//the tag is used as an identification for each game object; but not for individual instances of the object,
	//so all players have the same tag, but a player and a terrain object would have different tags
	virtual std::string getTag() const = 0;
	bool compareTag(const Actor* other) const;


	template<class T>
	//gets a pointer to the given behavior if the object has one, or nullptr otherwise
	//this is VERY slow because of the dynamic cast, so set this up in the start() functions
	//of all behaviors and actors
	T* getBehavior() {
		for (auto &c : components) {
			auto ret = dynamic_cast<T*>(c.get());
			if (ret != nullptr) {
				return ret;
			}
		}

		return nullptr;
	}

	template<class T>
	//adds a behavior to this object and returns a pointer to said behavior
	//this is VERY slow because of the dynamic cast, so set this up in the start() functions
	//of all behaviors and actors
	T* addBehavior() {
		T* t = new T();
		auto comp = dynamic_cast<Behavior*>(t);
		if (comp != nullptr) {
			components.push_back(std::unique_ptr<Behavior>(comp));
			comp->parent = this;
			return t;
		}
		else {
			return nullptr;
		}
	}

	std::vector<std::unique_ptr<Behavior>> components;
	Level* owner;
};

