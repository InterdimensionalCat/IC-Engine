#pragma once
#include "StaticBody.h"

class OneWayBody :
	public StaticBody
{
public:
	virtual int getType() {
		return 2;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setActiveEdge(int ind);

	int activeEdgeInd = 0;
};

