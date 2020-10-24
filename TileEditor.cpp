#include "include.h"
#include "TileEditor.h"
#include "TileButton.h"
#include "Tile.h"
#include "PhysicsBody.h"
#include "PolygonBody.h"
#include "TileSet.h"

TileEditor::TileEditor(TileSet* parent, Tile* initialedit, RenderWindow* window) : parent(parent), window(window) {
	tilesprite.setTexture(*parent->texture);
	View zoomedview = window->getView();
	zoomedview.zoom(0.1f);
	window->setView(zoomedview);

	setEdit(initialedit);
}

void TileEditor::setEdit(Tile* toedit) {
	buttons.clear();
	selected = nullptr;
	tiletoedit = toedit;
	for (auto &e : tiletoedit->body->getBody().edges) {
		buttons.push_back(TileButton(Vector2f(e.start.x, e.start.y)));
	}
	tilesprite.setTextureRect(IntRect(tiletoedit->texpos.x, tiletoedit->texpos.y, parent->tilesize, parent->tilesize));
}

void TileEditor::start() {
	Actor::start();
}

void TileEditor::tick(InputHandle* input) {
	//tilesprite.setPosition();
	auto &v = window->getView().getCenter();
	auto &v1 = Vector2f(tilesprite.getLocalBounds().width / 2.0f, tilesprite.getLocalBounds().width / 2.0f);
	tilesprite.setPosition(v - v1);

}

void TileEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//Actor::draw(target, states);
	target.draw(tilesprite, states);
	//VertexArray lines;
	//lines.setPrimitiveType(Lines);
	for (auto& b : buttons) {
		target.draw(b, states);
	//	Vertex vert;
	//	vert.position = b.pos;
	//	vert.color = Color(255, 0, 0, 255);
	//	lines.append(vert);
	}

	//target.draw(lines);
}