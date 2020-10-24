#include "include.h"
#include "TileDriver.h"
#include <algorithm>
#include <sstream>
#include <fstream>

ofstream outputFile;
stringstream fileBackup;
ifstream inputFile;
bool meters = true;
float height;
float width;

vector<vector<Vertex>> lines;
//vector<pair<int, Vector2f>> squares;
vector<vector<char>> gameMap;
Vector2f offset(0, 0);
Vector2f runningOffset(0, 0);
vector<Vector2f> vFill(0);
int numTerrain = 0;
char currentType = 'a';

//Tilemap map;
Texture* tileset;

class squareEqual {
public:
	bool operator () (const pair<int, Vector2f> &lhs, const pair<int, Vector2f> &rhs) const {
		return lhs.second == rhs.second;
	}
};

class posSort {
public:
	bool operator () (const pair<int, Vector2f> &lhs, const pair<int, Vector2f> &rhs) const {
		int l = lhs.second.y * width + lhs.second.x;
		int r = rhs.second.y * width + rhs.second.x;
		return l < r;
	}
};

bool save() {
	//squareEqual sq;
	//posSort so;
	//convert 2d vec into unique sorted 1d vec for saving
	vector<pair<char, Vector2f>>squares;
	for (int i = 0; i < gameMap.size(); i++) {
		for (int j = 0; j < gameMap.at(0).size(); j++) {
			if (gameMap.at(i).at(j) != 0) {
				char aaa = gameMap.at(i).at(j);
				Vector2f aaa2 = Vector2f((float)i, (float)j);
				squares.emplace_back(aaa, aaa2);
			}
		}
	}

	//std::sort(squares.begin(), squares.end(), so);
	//auto it = std::unique(squares.begin(), squares.end(), sq);
	//squares.resize(std::distance(squares.begin(), it));

	for (const auto &a : squares) {
#ifdef _DEBUG
		//cout << "Wrote block of type " << a.first << " at pos " << a.second;
#endif
		outputFile << a.first << " " << a.second.x << " " << a.second.y << "\n";
	}
	squares.clear();
	return true;
}

void updateArea(int i, int j, bool controlClick) {
	if (controlClick) {
#ifdef _DEBUG
		cout << "Square deleted at " << i << " " << j << "\n";
#endif
		gameMap.at(i).at(j) = '\0';
	}
	else {
#ifdef _DEBUG
		cout << "Square of type " << currentType << " created at " << i << " " << j << "\n";
#endif
		gameMap.at(i).at(j) = currentType;
	}
}

void updateInput(RenderWindow &window) {

	bool controlClick = Keyboard::isKeyPressed(Keyboard::LControl);
	bool shiftClick = Keyboard::isKeyPressed(Keyboard::LShift);
	if (shiftClick) {
		if (vFill.size() >= 2) {
			vFill.pop_back();
		}
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

		Vector2f pos = Vector2f(toMeters(mouseCoords.x), toMeters(mouseCoords.y));
		vFill.push_back(pos);
	}
	else {
		if (vFill.size() == 2) {
			Vector2i pt1(round(vFill.at(0).x), round(vFill.at(0).y));
			Vector2i pt2(round(vFill.at(1).x), round(vFill.at(1).y));
			for (int i = pt1.y; i < pt2.y; i++) {
				for (int j = pt1.x; j < pt2.x; j++) {
					//squares.push_back(pair<int, Vector2f>(currentType, Vector2f(j,i)));
					updateArea(j, i, controlClick);
				}
			}
			vFill.clear();
		}
	}

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();

		if (event.type == Event::KeyPressed) {
			//change hitbox type
			if (event.key.code == Keyboard::Num1) {
				currentType = 'a';
				cout << "Current type: a\n";
			}
			if (event.key.code == Keyboard::Num2) {
				currentType = 'b';
				cout << "Current type: b\n";
			}
			if (event.key.code == Keyboard::Num3) {
				currentType = 'c';
				cout << "Current type: c\n";
			}
			if (event.key.code == Keyboard::Num4) {
				currentType = 'd';
				cout << "Current type: d\n";
			}
			if (event.key.code == Keyboard::Num5) {
				currentType = 'e';
				cout << "Current type: e\n";
			}

			if (event.key.code == Keyboard::H) {
				cout << "Controls List: \n";
				cout << "Enter : save\n";
				cout << "WASD : scroll\n";
				cout << "num 1-9 : change type\n";
				cout << "Left click : place tile\n";
				cout << "Hold shift : fill area\n";
				cout << "Hold control : delete mode\n";
			}

			if (event.key.code == Keyboard::Z) {
				//squares.pop_back();
			}
			if (event.key.code == Keyboard::Enter) {
				if (save()) {
					cout << "Saved successfully!\n";
				}
				else {
					cout << "Save failed!\n";
				}
			}
		}


		if (event.type == Event::MouseButtonPressed) {
			Vector2i mouseCoords = Mouse::getPosition(window);
			mouseCoords += (Vector2i)runningOffset;
			if (mouseCoords.x > width) {
				mouseCoords.x = width - toPixels(1.0f);
			}
			if (mouseCoords.x < 0) {
				mouseCoords.x = 0;
			}
			if (mouseCoords.y > height) {
				mouseCoords.y = height - toPixels(1.0f);
			}
			if (mouseCoords.y < 0) {
				mouseCoords.y = 0;
			}

			Vector2f pos = Vector2f(toMeters(mouseCoords.x), toMeters(mouseCoords.y));
			pos = Vector2f(floor(pos.x), floor(pos.y));
			//squares.push_back(pair<int, Vector2f>(currentType, pos));
			updateArea(pos.x, pos.y, controlClick);
			//;; gameMap.at(pos.x).at(pos.y) = currentType;
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

	//draw lines
	for (auto vert : lines) {
		Vertex line[2] = { vert.at(0), vert.at(1) };
		window.draw(line, 2, Lines);
	}

	while (mwidth >= 0) {
		Vertex line[2] = { Vector2f(toPixels(mwidth), 0), Vector2f(toPixels(mwidth), height) };
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

	//draw tiles

	vector <pair<char, Vector2f>>squares;
	for (int i = 0; i < gameMap.size(); i++) {
		for (int j = 0; j < gameMap.at(0).size(); j++) {
			if (gameMap.at(i).at(j) != '\0') {
				squares.push_back(
					pair<char, Vector2f>(gameMap.at(i).at(j), Vector2f(i, j))
				);
			}
		}
	}

	for (auto pair : squares) {
		auto &pos = pair.second;
		RectangleShape rect;
		rect.setPosition(toPixels(pos.x), toPixels(pos.y));
		rect.setSize(Vector2f(toPixels(1.0f), toPixels(1.0f)));
		rect.setTexture(tileset);
		int offset = 0;
		if (pair.first == 'a') {
			//rect.setFillColor(Color::Red);
			offset = 1;
		}
		if (pair.first == 'b') {
			//rect.setFillColor(Color::Blue);
			offset = 2;
		}
		if (pair.first == 'c') {
			//rect.setFillColor(Color::Red);
			offset = 3;
		}
		if (pair.first == 'd') {
			//rect.setFillColor(Color::Blue);
			offset = 4;
		}
		if (pair.first == 'e') {
			//rect.setFillColor(Color::Blue);
			offset = 5;
		}
		rect.setTextureRect(IntRect(60 * offset, 0, 60, 60));
		//cout << rect.getTextureRect().top << " " << rect.getTextureRect().left << "\n";
		//cout << rect.getTextureRect().width << " " << rect.getTextureRect().height << "\n";
		window.draw(rect);

	}


	if (vFill.size() == 2) {
		Vector2f dim = vFill.at(1) - vFill.at(0);
		dim = Vector2f(toPixels(dim.x), toPixels(dim.y));
		Vector2f pos = vFill.at(0);
		RectangleShape rect;
		rect.setPosition(toPixels(pos.x), toPixels(pos.y));
		rect.setSize(dim);
		rect.setOutlineColor(Color::Red);
		rect.setFillColor(Color(0,0,0,0));
		rect.setOutlineThickness(3);
		window.draw(rect);
	}
}
void editorLoop() {
	int W = 1920;
	int H = 1080;
	RenderWindow window(VideoMode(W, H), "Crystal Level Editor(Tiles)");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	//set a view. breaks mouseCoords

	//auto a = window.getView();
	//a.zoom(0.5);
	//window.setView(a);

	cout << "Entered editor mode, current tile selection is: " << currentType << "\n";
	cout << "Press H for controls\n";

	while (window.isOpen())
	{
		window.clear(Color(25, 25, 25));
		updateInput(window);
		draw(window);
		window.display();
	}
}

bool loadFile() {
	outputFile.clear();
	fileBackup >> width;
	cout << "Width in meters: " << width;
	string space;
	//fileBackup >> space;
	//outputFile << space;
	fileBackup >> height;
	outputFile << height;
	cout << "\nHeight in meters: " << height << "\n";
	//fileBackup >> space;
	//outputFile << space;
	outputFile << "\n";
	if (width <= 0 || height <= 0) {
		cout << "invalid input file, will recreate \n";
		outputFile.clear();
		return false;
	}
	gameMap = vector<vector<char>>(width, vector<char>(height, 0));
	width = toPixels(width);
	height = toPixels(height);
	char type;
	int i;
	int j;
	while (fileBackup >> type >> i >> j) {
		gameMap.at(i).at(j) = type;
	}
	return true;
}

void recieveInput() {
	//take in dimension input
	string output;

	cout << "Enter file name: ";
	cin >> output;
	inputFile.open(GetCurrentWorkingDir() + "/maps/" + output + ".mmp");
	if (!inputFile.is_open()) {
		cout << "File does not exist, creating new file\n";
		outputFile.open(GetCurrentWorkingDir() + "/maps/" + output + ".mmp");
		if (!outputFile.is_open()) {
			cerr << "open failed\n";
			exit(1);
		}
		cout << "Enter width (Meters): ";
		cin >> width;
		outputFile << width;
		outputFile << " ";
		cout << "Enter height (Meters): ";
		cin >> height;
		outputFile << height;
		outputFile << "\n";
		gameMap = vector<vector<char>>(width, vector<char>(height, 0));
		width = toPixels(width);
		height = toPixels(height);
	}
	else {
		cout << "File exists, opening\n";
		string str;
		//ostringstream fileBackup;
		while (getline(inputFile, str)) {
			cout << str;
			cout << "\n";
			fileBackup << str;
			fileBackup << "\n";
		}
		inputFile.close();
		outputFile.open(GetCurrentWorkingDir() + "/maps/" + output + ".mmp");
		if (!outputFile.is_open()) {
			cerr << "open failed\n";
			exit(1);
		}


		if (!loadFile()) {
			cout << "Enter width (Meters): ";
			cin >> width;
			outputFile << width;
			outputFile << " ";
			cout << "Enter height (Meters): ";
			cin >> height;
			outputFile << height;
			outputFile << "\n";
			gameMap = vector<vector<char>>(width, vector<char>(height, 0));
			width = toPixels(width);
			height = toPixels(height);
		}
	}

	tileset = new Texture();
	tileset->loadFromFile(GetCurrentWorkingDir() + "/tilesets/technoTest60px.png");

	editorLoop();

	outputFile.close();
	delete tileset;
}