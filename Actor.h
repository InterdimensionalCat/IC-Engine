#pragma once
#include <vector>

class Behavior;

class Actor :
	public Drawable
{
public:
	virtual ~Actor() {}
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual string getTag() const = 0;
	bool compareTag(const Actor* other) const;

	template<class T>
	T* getBehavior() {
		for (auto &c : components) {
			auto ret = dynamic_pointer_cast<T>(c);
			if (ret) {
				return ret.get();
			}
		}

		return nullptr;
	}

	template<class T>
	T* addBehavior() {
		shared_ptr<T> t = make_shared<T>();

		auto comp = dynamic_pointer_cast<Behavior>(t);
		if (comp) {
			components.push_back(comp);
			comp->parent = this;
			return t.get();
		}
		else {
			return nullptr;
		}
	}

	std::vector<shared_ptr<Behavior>> components;
};

