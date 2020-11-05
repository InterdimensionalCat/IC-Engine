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
	//Actor(const Actor& other) = delete;
	//Actor& operator=(const Actor& other) = delete;

	virtual void tick(std::shared_ptr<InputHandle>& input);
	virtual void draw(std::shared_ptr<Renderer>& renderer);
	virtual std::string getTag() const = 0;
	bool compareTag(const std::shared_ptr<Actor>& other) const;

	template<class T>
	std::shared_ptr<T> getBehavior() {
		for (auto &c : components) {
			auto ret = std::dynamic_pointer_cast<T>(c);
			if (ret.get() != nullptr) {
				return ret;
			}
		}

		return std::shared_ptr<T>(nullptr);
	}

	template<class T>
	std::shared_ptr<T> addBehavior() {
		std::shared_ptr<T> t = std::make_shared<T>();

		auto comp = std::dynamic_pointer_cast<Behavior>(t);
		if (comp.get() != nullptr) {
			components.push_back(std::shared_ptr(comp));
			comp->parent = std::shared_ptr<Actor>(this);
			return t;
		}
		else {
			return std::shared_ptr<T>(nullptr);
		}
	}

	std::vector<std::shared_ptr<Behavior>> components;
	std::shared_ptr<Level> owner;
};

