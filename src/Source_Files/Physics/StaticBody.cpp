#include "include.h"
#include "Staticbody.h"
#include "GameTransform.h"
#include "Polygonbody.h"
#include "Composite.h"
#include"PhysicsEngine.h"


StaticBody::StaticBody() {

}

void StaticBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//polygon draw

	ConvexShape drawshape;
	drawshape.setPointCount(body.edges.size());
	for (size_t i = 0; i < body.edges.size(); i++) {
		drawshape.setPoint(i, body.edges.at(i).start);
	}
	//drawshape.setOrigin(pos);
	drawshape.setOutlineColor(Color::Black);
	drawshape.setFillColor(Color(255, 0, 0, 100));
	drawshape.setOutlineThickness(1);
	target.draw(drawshape, states);

	//draw normals


	for (size_t i = 0; i < body.edges.size(); i++) {

		VertexArray line(Lines, 2);

		Vector2f midp = body.edges.at(i).end - body.edges.at(i).start;
		midp = Vector2f(midp.x / 2.0f, midp.y / 2.0f) + body.edges.at(i).start;
		line[0] = midp;
		line[1] = midp + body.edges.at(i).normal * 0.3f;

		if (body.edges.at(i).active) {
			line[0].color = Color::Yellow;
			line[1].color = Color::Yellow;
		}
		else {
			line[0].color = Color::Black;
			line[1].color = Color::Black;
		}

		target.draw(line, states);
	}

	//draw center

	float radius = 0.5;

	CircleShape drawS;
	Vector2f cent = this->getCentroid();
	drawS.setPosition(Vector2f(cent.x, cent.y));
	drawS.setRadius(radius);
	drawS.setOutlineColor(Color::Yellow);
	drawS.setFillColor(Color::Yellow);
	drawS.setOutlineThickness(3);
	target.draw(drawS, states);
}

void StaticBody::Register(PhysicsEngine* engine) {
	engine->addBody(this);
}