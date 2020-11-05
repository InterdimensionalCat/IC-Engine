#pragma once
#include "Actor.h"
#include "GameTransform.h"
#include "PhysicsBody.h"
#include "Space2D.h"

class TestActor :
	public Actor
{
public:
	void start() {

		body = addBehavior<PhysicsBody>();
		trans = addBehavior<GameTransform>();

		auto pos = s2d::Vec(3 * 60, 5 * 60);
		auto size = s2d::Vec(4 * 60, 4 * 60);

		trans->setPos(s2d::Point(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));

		//for (int i = 0; i < 7; i++) {
		//	int variance = i % 2 == 0 ? 1 : -1;
		//	auto dimvec = pos + s2d::Vec((0.75f + (float)i / 6) * i, variance * 2 * (float)i) * 60.0f;
		//	s2d::Poly b = s2d::Poly(s2d::Rectangle(s2d::Point(size.x, size.y), s2d::Dimension(dimvec.x, dimvec.y)));
		//	body->addPoly(b, false);
		//	body->setEdgeActive(i, 0, true);
		//	body->setType(CollisionType::Static);
		//}

		s2d::Poly b = s2d::Poly(s2d::Rectangle(s2d::Point(pos.x, pos.y), s2d::Dimension(size.x, size.y)));
		body->addPoly(b, true);
		//body->setEdgeActive(0, 0, true);
		body->setType(CollisionType::Static);

		body->setDensity(1.5f);

		Actor::start();
	}

	void draw(std::shared_ptr<Renderer>& renderer) {
		for (auto b : body->getBodies()) {
			auto drawn = b.getDrawableSFMLPolygon(5.0, sf::Color(0, 255, 0, 50), sf::Color(255, 0, 0, 255));
			renderer->window->draw(drawn, renderer->states);
		}
		Actor::draw(renderer);
	}

	string getTag() const {
		return "terrain";
	}


	std::shared_ptr<GameTransform> trans;
	std::shared_ptr<PhysicsBody> body;
};

