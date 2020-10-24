#include "include.h"
#include "PolygonBody.h"
#include "PhysMath.h"
#include "Behavior.h"


PolygonBody::PolygonBody() {
	edges = vector<Edge>(0);
}


float PolygonBody::area() {
	float area = 0.0f;
	for (auto &e : edges) {
		area += (e.start.x + e.end.x) *
			(e.start.y - e.end.y);
	}

	return abs(area / 2.0f);
}

void PolygonBody::translate(const Vector2f &amount) {
	for (auto& e : edges) {
		e.start += amount;
		e.end += amount;
	}
}

FloatRect PolygonBody::getAABB() {
	float minx = numeric_limits<float>::infinity();
	float miny = numeric_limits<float>::infinity();

	float maxx = -numeric_limits<float>::infinity();
	float maxy = -numeric_limits<float>::infinity();

	for (Edge &e : edges) {
		if (e.start.x > maxx) {
			maxx = e.start.x;
		}

		if (e.start.x < minx) {
			minx = e.start.x;
		}

		if (e.start.y > maxy) {
			maxy = e.start.y;
		}

		if (e.start.y < miny) {
			miny = e.start.y;
		}
	}


	return FloatRect(Vector2f(minx, miny), Vector2f(maxx - minx, maxy - miny));
}