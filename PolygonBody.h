#pragma once
#include "PhysMath.h"

//internal class used for polygon edges
class Edge {
public:
	Edge() : start(Z_VEC), end(Z_VEC), normal(Z_VEC) {}
	Edge(const Vector2f &start, const Vector2f &end) : start(start), end(end) {
		normal = UnitNormal(getVec());
	}

	Vector2f getVec() {
		return end - start;
	}

	Vector2f start;
	Vector2f end;
	Vector2f normal;
	bool active = true;
};

//convex polygon is centered at 0,0 by default,
//any object translating the polygon must do so itself
//edges are clockwise order
class PolygonBody {
public:

	//constructs a 1.0x1.0 square
	PolygonBody();

	//returns the area of the polygon
	float area();

	//move the shape
	void translate(const Vector2f &amount);

	FloatRect getAABB();

	//the edges of the polygon
	vector<Edge> edges;
};
