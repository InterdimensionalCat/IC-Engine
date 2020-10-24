#include "include.h"
#include "Driver.h"

ofstream outputFile;
bool meters = true;
float height;
float width;
vector<CircleShape> targets;
vector<vector<Vertex>> lines;
vector<vector<Vector2f>> terrainVert(1, vector<Vector2f>(0));
Vector2f offset(0, 0);
Vector2f runningOffset(0,0);
int numTerrain = 0;

void updateInput(RenderWindow &window) {
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();

		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::F) {
				//finish terrain polygon
				if (terrainVert.at(numTerrain).size() >= 2) {
					vector<Vertex> line = { toPixels(terrainVert.at(numTerrain).at((int)terrainVert.at(numTerrain).size() - 1)), toPixels(terrainVert.at(numTerrain).at(0)) };
					lines.push_back(line);
					outputFile << "PolygonDef\n";
					outputFile << (int)terrainVert.at(numTerrain).size() << "\n";
					for (int i = 0; i < (int)terrainVert.at(numTerrain).size(); i++) {
						outputFile << terrainVert.at(numTerrain).at(i).x << " " << terrainVert.at(numTerrain).at(i).y << " ";
					}
					terrainVert.push_back(vector<Vector2f>(0));
					numTerrain++;
					outputFile << "\n";
				}
			}

			if (event.key.code == Keyboard::N) {
				//finish a terrain object
				if (terrainVert.at(numTerrain).size() >= 1) {
					outputFile << "TerrainDef\n";
					outputFile << (int)terrainVert.at(numTerrain).size() << "\n";
					for (int i = 0; i < (int)terrainVert.at(numTerrain).size(); i++) {
						outputFile << terrainVert.at(numTerrain).at(i).x << " " << terrainVert.at(numTerrain).at(i).y << " ";
					}
					terrainVert.push_back(vector<Vector2f>(0));
					numTerrain++;
					outputFile << "\n";
				}
			}

			if (event.key.code == Keyboard::Z) {
				if (terrainVert.at(numTerrain).size() >= 2) {
					lines.pop_back();
				}

				if (terrainVert.at(numTerrain).size() >= 1) {
					terrainVert.at(numTerrain).pop_back();
					targets.pop_back();
				}
			}
		}

		if (event.type == Event::MouseButtonPressed) {
			Vector2i mouseCoords = Mouse::getPosition(window);
			mouseCoords += (Vector2i)runningOffset;
			if (mouseCoords.x > width) {
				mouseCoords.x = width;
			}
			if (mouseCoords.x < 0) {
				mouseCoords.x = 0;
			}
			if (mouseCoords.y > height) {
				mouseCoords.y = height;
			}
			if (mouseCoords.y < 0) {
				mouseCoords.y = 0;
			}
			CircleShape vert;
			vert.setPosition((Vector2f)mouseCoords - Vector2f(2.5, 2.5));
			vert.setFillColor(Color::Red);
			vert.setRadius(5);
			targets.push_back(vert);
			terrainVert.at(numTerrain).push_back(Vector2f(toMeters(mouseCoords.x), toMeters(mouseCoords.y)));
			int currentSize = (int)terrainVert.at(numTerrain).size();
			if (currentSize - 2 >= 0) {
				vector<Vertex> line = { toPixels(terrainVert.at(numTerrain).at(currentSize - 2)), toPixels(terrainVert.at(numTerrain).at(currentSize - 1)) };
				lines.push_back(line);
			}
		}
	}

	
	offset = Vector2f(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		offset += Vector2f(-5, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		offset += Vector2f(0, 5);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		offset += Vector2f(5, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		offset += Vector2f(0, -5);
	}
	runningOffset += offset;
}
void draw(RenderWindow &window) {
	Vector2u screenSize = window.getSize();
	float mheight = toMeters(height);
	float mwidth = toMeters(width);
	View shift = window.getView();
	shift.move(offset);
	window.setView(shift);

	for (Drawable &draw : targets) {
		window.draw(draw);
	}

	for (auto vert : lines) {
		Vertex line[2] = { vert.at(0), vert.at(1) };
		window.draw(line, 2, Lines);
	}

	while (mwidth >= 0) {
		Vertex line[2] = { Vector2f(toPixels(mwidth), 0), Vector2f(toPixels(mwidth), height)};
		line[0].color = Color::Green;
		line[1].color = Color::Blue;
		window.draw(line, 2, Lines);
		mwidth -= 1.0f;
	}

	while (mheight >= 0) {
		Vertex line[2] = { Vector2f(0, toPixels(mheight)), Vector2f(width, toPixels(mheight)) };
		line[0].color = Color::Blue;
		line[1].color = Color::Green;
		window.draw(line, 2, Lines);
		mheight -= 1.0f;
	}
}
void editorLoop() {
	int W = 1920;
	int H = 1080;
	RenderWindow window(VideoMode(W, H), "Crystal Level Editor");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);


	while (window.isOpen())
	{
		window.clear(Color(25, 25 ,25));
		updateInput(window);
		draw(window);
		window.display();
	}
}
void recieveInput() {
	//take in dimension input
	string output;

	cout << "Enter file name: ";
	cin >> output;
	outputFile.open(GetCurrentWorkingDir() + "/maps/" + output + ".mmp");
	if (!outputFile.is_open()) {
		cerr << "open failed\n";
		exit(1);
	}



	cout << "\n Enter width (Meters): ";
	cin >> width;
	outputFile << width;
	outputFile << " ";
	cout << "\n Enter height (Meters): ";
	cin >> height;
	outputFile << height;
	outputFile << "\n";
	width = toPixels(width);
	height = toPixels(height);
	editorLoop();

	outputFile.close();
}