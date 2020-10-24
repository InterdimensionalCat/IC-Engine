#include "include.h"
#include "TileButton.h"

TileButton::TileButton(const Vector2f &pos) : pos(pos) {
	drawshape.setPosition(pos);
	drawshape.setRadius(radius);
	drawshape.setOutlineThickness(1);
	drawshape.setOutlineColor(Color(100, 100, 200, 255));
	drawshape.setFillColor(Color(100, 100, 200, 50));
}

void TileButton::hovered() {
	drawshape.scale(1.33, 1.33);
}

void TileButton::unhovered() {
	drawshape.setScale(1, 1);
}

void TileButton::selected() {
	drawshape.setOutlineColor(Color(200, 50, 200, 255));

}

void TileButton::unselected() {
	drawshape.setOutlineColor(Color(100, 100, 200, 255));
}

void TileButton::move(Vector2f newpos) {
	pos = newpos;
	drawshape.setPosition(newpos);
}

void TileButton::draw(RenderTarget& target, RenderStates states) const {
	target.draw(drawshape, states);
}