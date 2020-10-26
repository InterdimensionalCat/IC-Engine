#pragma once
#include "PhysicsBody.h"

class StaticBody : 
	public PhysicsBody
{
public:

	StaticBody();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Register(PhysicsEngine* engine);

	virtual int getType() {
		return 1;
	}

private:
};

