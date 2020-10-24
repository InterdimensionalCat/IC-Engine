#pragma once

class PhysicsBody;

class Tile
{
public:
	Tile();
	Tile(const std::string &type, const Vector2i &texpos, PhysicsBody* body);
	std::string getType();
	void rotate();
	void flip();
	PhysicsBody* body;
	bool flipped;
	int rotation; //0, 90, 180, 270, 360
	std::string type;
	Vector2i texpos;
};

