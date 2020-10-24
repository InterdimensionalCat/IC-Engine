#include "include.h"
#include "Tile.h"
#include "PhysicsBody.h"
#include <string>


Tile::Tile() : body(nullptr), flipped(false), rotation(0), type("AIR"), texpos(0,0) {

}


Tile::Tile(const std::string &type, const Vector2i &texpos, PhysicsBody* body) : flipped(false), rotation(0), type(type), texpos(texpos), body(body) {

}

std::string Tile::getType() {
	return type;
}

void Tile::rotate() {
	rotation += 90;
	if (rotation > 270) {
		rotation = 0;
	}
}

void Tile::flip() {
	flipped = ! flipped;
}
