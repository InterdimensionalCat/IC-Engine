#pragma once
#include <vector>
#include "Behavior.h"
#include <memory>
#include <string>

class Level;

class Actor
{
public:
	virtual ~Actor() {}
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	virtual std::string getTag() const = 0;
	bool compareTag(const Actor* other) const;

	template<class T>
	T* getBehavior() {
		for (auto &c : components) {
			auto ret = std::dynamic_pointer_cast<T>(c);
			if (ret) {
				return ret.get();
			}
		}

		return nullptr;
	}

	template<class T>
	T* addBehavior() {
		std::shared_ptr<T> t = std::make_shared<T>();

		auto comp = std::dynamic_pointer_cast<Behavior>(t);
		if (comp) {
			components.push_back(comp);
			comp->parent = this;
			return t.get();
		}
		else {
			return nullptr;
		}
	}

	std::vector<std::shared_ptr<Behavior>> components;
	Level* owner;
};

