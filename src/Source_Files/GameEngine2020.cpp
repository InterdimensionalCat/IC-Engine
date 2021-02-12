#include "include.h"
#include "SettingsProvider.h"
#include "LoggerProvider.h"
#include "InputHandle.h"
#include "AudioHandle.h"
//#include "Renderer.h"

#include "Scene.h"

using namespace ic;


void updateInput(Renderer& renderer) {
	renderer.updateInput();
}

//Sends input events to everything that needs it
void handleInput(InputHandle& input) {}

//updates all non-input-non-physics game logic
void updateAI() {}
//updates all physics-related game logic
void updatePhysics(const float dt) {}

//handles audio related stuff
void updateAudio(AudioHandle& audio) {}

//renders game
void draw(float interpol, Renderer& renderer) {
	renderer.preRender(interpol);
	renderer.postRender();
}

void game() {
	//create window, set height, width name, framerate set vsync if enabled
	auto renderer = std::make_unique<Renderer>();
	auto audio = std::make_unique<AudioHandle>();

	//Game Loop Objects:
	std::unique_ptr<sf::Clock> timer;
	float dt = 0.0f;
	float currentfps = 0;
	sf::Clock fpstimer = sf::Clock();

	//initialize clock and gameloop time accumulator
	timer = std::make_unique<sf::Clock>();
	double accumulator = 0;

	auto input = std::make_unique<InputHandle>();

	//main game loop
	while (SettingsProvider::getSetting<bool>("running"))
	{
		//update accumulator with time passed
		double deltaTime = timer->getElapsedTime().asSeconds();
		accumulator += deltaTime;
		timer->restart();

		const float targetDT = SettingsProvider::getSetting<float>("targetDT");


		if (SettingsProvider::getSetting<TimeStepType>("TimeStepType") == TimeStepType::Variable) {
			//variable timestep

			updateInput(*renderer);
			handleInput(*input);
			updateAI();
			updatePhysics((float)accumulator);
			updateAudio(*audio);

			accumulator = 0;
		}
		else {
			//fixed time step
			while (accumulator >= targetDT) {

				updateInput(*renderer);
				handleInput(*input);
				updateAI();
				updatePhysics(targetDT);
				updateAudio(*audio);

				accumulator -= targetDT;
			}
		}


		//draw
		draw((float)accumulator / targetDT, *renderer);
	}
}

void stop() {
#ifdef debug_mode
	LoggerProvider::log("Game Closing\n");
#endif
	SettingsProvider::setSetting<bool>("running", false);
	//running = false;
	//renderer->window->close();
}

int main(int argc, char *argv[])
{

	std::cout.flush();

#ifdef debug_mode
	LoggerProvider::log("Running in debug mode", LogSeverity::Debug);
	LoggerProvider::log("Current working directory: " + fs::current_path().generic_u8string(), LogSeverity::Info);
#endif

#ifdef _WIN32
	LoggerProvider::log("Current OS is: Windows\n");
	LoggerProvider::log("Windows debug version will check for memory leaks\n");
	//check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

#ifdef __linux__
	LoggerProvider::log("Current OS is: Linux\n");
#endif

#ifdef __APPLE__
	LoggerProvider::log("Current OS is: Mac OSX\n");
#endif
	ic::Scene scene;
	scene.testActorUID();
	//game();
	return 0;
}