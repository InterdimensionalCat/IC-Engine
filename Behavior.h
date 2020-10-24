#pragma once

class Actor;

class Behavior :
	public Drawable
{
public:

	virtual ~Behavior() {}
	virtual void start() = 0;
	virtual void tick(InputHandle* input) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	Actor* getActor();
private:

	friend class Actor;

	Actor* parent;
};

