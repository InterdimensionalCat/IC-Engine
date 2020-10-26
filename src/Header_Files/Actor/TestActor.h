#pragma once
#include "Actor.h"
#include "GameTransform.h"
#include "StaticBody.h"
#include "Composite.h"
#include "OneWayBody.h"

class TestActor :
	public Actor
{
public:
	void start() {

		comp = addBehavior<Composite>();
		trans = addBehavior<GameTransform>();

		Vector2f pos = Vector2f(1 * 60, 0.5 * 60);
		Vector2f size = Vector2f(5 * 60, 0.2 * 60);

		trans->setPos(pos);

		for (int i = 0; i < 7; i++) {
			OneWayBody* b = new OneWayBody();
			int variance = i % 2 == 0 ? 1 : -1;
			b->constructQuad(size, pos + Vector2f((0.75 + i / 6) * i, variance * 2 * i) * 60.0f);
			b->setActiveEdge(0);
			comp->addBody(b);
		}


		comp->setDensity(1.5);

		Actor::start();
	}

	string getTag() const {
		return "terrain";
	}


	GameTransform* trans;
	Composite* comp;
};

