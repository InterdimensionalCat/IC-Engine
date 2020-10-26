#include "include.h"



WindowData::WindowData(RenderWindow* wind) :
	window(wind),
	states(RenderStates::Default) {
	if (instance->vsync) {
		window->setVerticalSyncEnabled(true);
		cout << "V-Sync Enabled\n";
	}
	else {
		window->setFramerateLimit((unsigned int)instance->targetFPS);
		cout << "fps is " << instance->targetFPS << "\n";
	}

	window->setKeyRepeatEnabled(false);
}

Game::Game() {
	//initialize settings?
}


Game* instance = new Game();

void Game::tick(const float dt) {
	Game::dt = dt;
	manager->tick(input.get());
}

void Game::draw(const float interpol) {
	renderer->interpol = interpol;
	manager->draw(renderer.get());
}

void Game::game() {
	//create window, set height, width name, framerate set vsync if enabled
	renderer = make_unique<Renderer>(this);

	//initialize clock and gameloop time accumulator
	timer = make_unique<Clock>();
	double accumulator = 0;

	RenderWindow* wind = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);

	subwindows.emplace("MAIN", make_unique<WindowData>(wind));
	MainWindow = subwindows.at("MAIN").get();

	input = make_unique<InputHandle>(this);
	manager = make_unique<StateManager>(this);

	//main game loop
	while (running)
	{
		//update accumulator with time passed
		double deltaTime = timer->getElapsedTime().asSeconds();
		accumulator += deltaTime;
		timer->restart();

		//clear window of previous frame
		for (auto& wind : subwindows) {
			wind.second->get()->clear(Color(140, 140, 140, 255));
		}


		if (timeType == TimeStepType::Variable) {
			//variable timestep

			//recieve input
			input->updateInput();

			tick((float)accumulator);
			accumulator = 0;
		}
		else {
			//fixed time step
			while (accumulator >= targetDT) {

				//recieve input
				input->updateInput();

				tick(targetDT);
				accumulator -= targetDT;
			}
		}


		//draw
		draw((float)accumulator / targetDT);
		currentfps++;

		if (fpstimer.getElapsedTime().asSeconds() >= 1) {
			if (debug) {
				//cout << "fps: " << currentfps << "\n";
				cout << "fps: " << currentfps << "\n";
			}

			currentfps = 0;
			fpstimer.restart();
		}



		//display
		for (auto &wind : subwindows) {
			wind.second->get()->display();
		}
	}
}

void Game::stop() {
#ifdef _DEBUG
	cout << "Game Closing\n";
#endif
	running = false;
	for (auto &wind : subwindows) {
		wind.second->get()->close();
	}
}

int main(int argc, char *argv[])
{

	std::cout.flush();

#ifdef debug_mode
	cout << "Running in debug mode.\n";
	cout << "Current working directory: " << fs::current_path().generic_u8string() << "\n";
#endif

#ifdef _WIN32
	cout << "Current OS is: Windows\n";
	cout << "Windows debug version will check for memory leaks\n";
	//check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

#ifdef __linux__
	cout << "Current OS is: Linux\n";
#endif

#ifdef __APPLE__
	cout << "Current OS is: Mac OSX\n";
#endif

	instance->game();
	delete instance;
	return 0;
}