#include "include.h"
#include "SettingsProvider.h"
#include "Logger.h"


Game::Game() {
	//initialize settings?
}


Game* instance = new Game();

//updates the game logic (and handles basically everything that is not drawing)
void Game::tick(const float dt) {
	//Game::dt = dt;
	//manager->tick(input.get());
}

//renders the game to the screen
void Game::draw(const float interpol) {
	//renderer->interpol = interpol;
	//renderer->states = RenderStates::Default;
	//manager->draw(renderer.get());
}

void Game::game() {
	//create window, set height, width name, framerate set vsync if enabled
	renderer = std::make_unique<Renderer>();

	//initialize clock and gameloop time accumulator
	timer = std::make_unique<sf::Clock>();
	double accumulator = 0;

	renderer->window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(SettingsProvider::getSetting<int>("Width"), SettingsProvider::getSetting<int>("Height")), 
		SettingsProvider::getSetting<std::string>("Title")
	);

	if (SettingsProvider::getSetting<bool>("vsync")) {
		//V-sync doesnt really play nice with animations and I find that SFML can be
		//somewhat stuttery and I cant tell if V-sync makes it better or worse
		renderer->window->setVerticalSyncEnabled(true);
#ifdef debug_mode
		std::cout << "V-Sync Enabled\n";
#endif
	}
	else {
		renderer->window->setFramerateLimit((unsigned int)SettingsProvider::getSetting<float>("targetFPS"));
#ifdef debug_mode
		std::cout << "V-Sync disabled; fps is " << SettingsProvider::getSetting<float>("targetFPS") << "\n";
#endif
	}

	renderer->window->setKeyRepeatEnabled(false);

	input = std::make_unique<InputHandle>();
	manager = std::make_unique<StateManager>();

	//main game loop
	while (SettingsProvider::getSetting<bool>("running"))
	{
		//update accumulator with time passed
		double deltaTime = timer->getElapsedTime().asSeconds();
		accumulator += deltaTime;
		timer->restart();

		const float targetDT = SettingsProvider::getSetting<float>("targetDT");

		//clear window of previous frame
		renderer->window->clear(sf::Color(140, 140, 140, 255));


		if (SettingsProvider::getSetting<TimeStepType>("TimeStepType") == TimeStepType::Variable) {
			//variable timestep

			//recieve input
			if (!input->updateInput((float)accumulator, renderer->window.get())) {
				stop();
			}

			tick((float)accumulator);
			accumulator = 0;
		}
		else {
			//fixed time step
			while (accumulator >= targetDT) {

				//recieve input
				if (!input->updateInput((float)accumulator, renderer->window.get())) {
					stop();
				}

				tick(targetDT);
				accumulator -= targetDT;
			}
		}


		//draw
		draw((float)accumulator / targetDT);
		currentfps++;

		if (fpstimer.getElapsedTime().asSeconds() >= 1) {
			if (SettingsProvider::getSetting<bool>("debug")) {
				std::cout << "fps: " << currentfps << "\n";
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
	std::cout << "Game Closing\n";
#endif
	SettingsProvider::setSetting<bool>("running", false);
	//running = false;
	renderer->window->close();
}

int main(int argc, char *argv[])
{

	std::cout.flush();

#ifdef debug_mode
	//std::cout << "Running in debug mode.\n";
	//std::cout << "Current working directory: " << fs::current_path().generic_u8string() << "\n";
	logInstance.log("Running in debug mode", LogSeverity::Debug);
	logInstance.log("Current working directory: " + fs::current_path().generic_u8string(), LogSeverity::Info);
#endif

#ifdef _WIN32
	std::cout << "Current OS is: Windows\n";
	std::cout << "Windows debug version will check for memory leaks\n";
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