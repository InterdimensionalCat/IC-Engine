#include "include.h"
#include "TileSet.h"
#include "StaticBody.h"
#include "Composite.h"
#include "GameTransform.h"
TileSet::TileSet() {

}

TileSet::TileSet(const std::string &filename) : filename(filename) {

}

void TileSet::start() {
	texture = make_unique<Texture>();
	rendertex = make_unique<RenderTexture>();
	hitboxtex = make_unique<RenderTexture>();
	testcomp = addBehavior<Composite>();
	testtransform = addBehavior<GameTransform>();
	testtransform->start();
	testcomp->start();



	ifstream tsfIn;
	tsfIn.open(GetCurrentWorkingDir() + "/tilesets/" + filename + ".tsf");
	if (!tsfIn.is_open()) {
		throw TilesetLoadException(filename, GetCurrentWorkingDir() + "/tilesets/" + filename + ".tsf");
	}

	string texturename;
	getline(tsfIn, texturename);
	if (!texture->loadFromFile(GetCurrentWorkingDir() + "/tilesets/" + texturename + ".png")) {
		throw TextureLoadException(texturename, GetCurrentWorkingDir() + "/tilesets/" + texturename + ".png");
	}

	rendertex->create(texture->getSize().x, texture->getSize().y);

	tsfIn >> tilesize;
	tsfIn >> sizex;
	tsfIn >> sizey;

	tiles = vector<vector<Tile>>(sizex, vector<Tile>(sizey));

	string tileparse;
	getline(tsfIn, tileparse);
	getline(tsfIn, tileparse);
	if (tileparse.at(0) != '{') {
		return;
	}

	getline(tsfIn, tileparse);

	while (tileparse.at(0) != '}') {

		//create a new tile

		string type = tileparse;

		int tilex;
		int tiley;

		tsfIn >> tilex >> tiley;

		getline(tsfIn, tileparse);
		getline(tsfIn, tileparse);

		if (tileparse == "quad") {
			float quadx;
			float quady;

			tsfIn >> quadx >> quady;
			StaticBody* body = new StaticBody();
			body->constructQuad(Vector2f(tilex * tilesize, tiley * tilesize), Vector2f(quadx * tilesize, quady * tilesize));
			testcomp->addBody(body);
			tiles.at(tilex).at(tiley) = Tile(type, Vector2i(tilex * tilesize, tiley * tilesize), body);
			getline(tsfIn, tileparse);
			getline(tsfIn, tileparse);
			getline(tsfIn, tileparse);
		}
		else {
			if (tileparse == "poly") {
				vector<Vector2f> points;
				int num_points;
				tsfIn >> num_points;
				points.reserve(num_points);
				for (int i = 0; i < num_points; i++) {
					float px;
					float py;
					tsfIn >> px >> py;
					points.push_back(Vector2f(px, py));
				}

				StaticBody* body = new StaticBody();
				body->constructPoly(points, FloatRect(Vector2f(tilex * tilesize, tiley * tilesize), Vector2f(tilesize, tilesize)));
				testcomp->addBody(body);
				tiles.at(tilex).at(tiley) = Tile(type, Vector2i(tilex, tiley), body);
				getline(tsfIn, tileparse);
				getline(tsfIn, tileparse);
				getline(tsfIn, tileparse);
			}
			else {
				throw new MapIOException();
			}
		}
	}


	//set up tilemap for rendering

	buffer.setPrimitiveType(sf::Quads);
	buffer.setUsage(sf::VertexBuffer::Usage::Dynamic);
	buffer.create(sizex * sizey * 4);

	int offset = 0;

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < sizex; ++i) {
		for (unsigned int j = 0; j < sizey; ++j)
		{

			Tile* t = &tiles.at(i).at(j);

			// find its position in the tileset texture
			int tu = t->texpos.x;
			int tv = t->texpos.y;

			// get a pointer to the current tile's quad
			sf::Vertex quad[4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tilesize, j * tilesize);
			quad[1].position = sf::Vector2f((i + 1) * tilesize, j * tilesize);
			quad[2].position = sf::Vector2f((i + 1) * tilesize, (j + 1) * tilesize);
			quad[3].position = sf::Vector2f(i * tilesize, (j + 1) * tilesize);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tilesize, tv * tilesize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tilesize, tv * tilesize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tilesize, (tv + 1) * tilesize);
			quad[3].texCoords = sf::Vector2f(tu * tilesize, (tv + 1) * tilesize);

			buffer.update(quad, 4, offset);
			offset += 4;
		}
	}
}

void TileSet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	RenderStates customstates = RenderStates::Default;
	customstates.texture = texture.get();
	rendertex->draw(buffer, customstates);
	rendertex->display();
	Sprite texspr(rendertex->getTexture());

	target.draw(texspr, states);
	target.draw(*testcomp, states);

}
