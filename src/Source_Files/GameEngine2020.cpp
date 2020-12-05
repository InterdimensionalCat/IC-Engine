#include "include.h"


Game::Game() {
	//initialize settings?
}


Game* instance = new Game();

//updates the game logic (and handles basically everything that is not drawing)
void Game::tick(const float dt) {
	Game::dt = dt;
	manager->tick(input.get());
}

//renders the game to the screen
void Game::draw(const float interpol) {
	renderer->interpol = interpol;
	renderer->states = RenderStates::Default;
	manager->draw(renderer.get());
}

void Game::game() {
	//create window, set height, width name, framerate set vsync if enabled
	renderer = make_unique<Renderer>(instance);

	//initialize clock and gameloop time accumulator
	timer = make_unique<Clock>();
	double accumulator = 0;

	renderer->window = std::make_unique<RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE);

	if (instance->vsync) {
		//V-sync doesnt really play nice with animations and I find that SFML can be
		//somewhat stuttery and I cant tell if V-sync makes it better or worse
		renderer->window->setVerticalSyncEnabled(true);
#ifdef debug_mode
		cout << "V-Sync Enabled\n";
#endif
	}
	else {
		renderer->window->setFramerateLimit((unsigned int)instance->targetFPS);
#ifdef debug_mode
		cout << "V-Sync disabled; fps is " << instance->targetFPS << "\n";
#endif
	}

	renderer->window->setKeyRepeatEnabled(false);

	input = make_unique<InputHandle>(instance);
	manager = std::make_unique<StateManager>(instance);

	//main game loop
	while (running)
	{
		//update accumulator with time passed
		double deltaTime = timer->getElapsedTime().asSeconds();
		accumulator += deltaTime;
		timer->restart();

		//clear window of previous frame
		renderer->window->clear(Color(140, 140, 140, 255));


		if (timeType == TimeStepType::Variable) {
			//variable timestep

			//recieve input
			input->updateInput((float)accumulator);

			tick((float)accumulator);
			accumulator = 0;
		}
		else {
			//fixed time step
			while (accumulator >= targetDT) {

				//recieve input
				input->updateInput(targetDT);

				tick(targetDT);
				accumulator -= targetDT;
			}
		}


		//draw
		draw((float)accumulator / targetDT);
		currentfps++;

		if (fpstimer.getElapsedTime().asSeconds() >= 1) {
			if (debug) {
				cout << "fps: " << currentfps << "\n";
			}

			currentfps = 0;
			fpstimer.restart();
		}



		//display
		renderer->window->display();
	}
}

void Game::stop() {
#ifdef debug_mode
	cout << "Game Closing\n";
#endif
	running = false;
	renderer->window->close();
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