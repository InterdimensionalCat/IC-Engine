#include "include.h"
#include "Scene.h"

#include "BenchmarkLogger.h"

using namespace ic;

/**
 * @brief update function for the game engine
 * @details update function for the game engine,
 * all game logic gets updated during this function call
 * @param scene the scene for the engine
*/
void update(Scene& scene) {
	scene.update();
}

/**
 * @brief draw function for the game engine
 * @details draw function for the game engine,
 * everything gets drawn to the screen during this function call
 * @param interpol the calculated interpolation value for the frame,
 * since draw calls are not expected to land on a perfect frame boundry,
 * this allows for measures to be taken such that gameplay remains smooth
 * @param scene the scene for the engine
*/
void draw(const float interpol, Scene& scene) {
	scene.draw(interpol);
}

/**
 * @brief main game loop function, 
 * @details main game loop function,
 * initalizes various timing variables to time step properly
 * and creates the Scene object, the central object that manages
 * the game
*/
void game() {

	std::unique_ptr<sf::Clock> timer = std::make_unique<sf::Clock>();
	float dt = 0.0f;
	double accumulator = 0;

	auto scene = std::make_unique<Scene>();

	while (Settings::getRunning())
	{

		double deltaTime = timer->getElapsedTime().asSeconds();
		accumulator += deltaTime;
		timer->restart();

		const float targetDT = Settings::getTargetDT();


		if (Settings::getStepType() == TimeStepType::Variable) {
			//variable timestep
			update(*scene);
			accumulator = 0;
		}
		else {
			//fixed time step
			while (accumulator >= targetDT) {
				update(*scene);
				accumulator -= targetDT;
			}
		}


		//draw
		draw((float)accumulator / targetDT, *scene);
	}

	Logger::info("Game Closing.");
}

/**
 * @brief Primary entry point to the game engine,
 * @details Primary entry point to the game engine, 
 * starts up the logger and intializes settings
 * @param argc number of args passed in from the command line
 * @param argv the args passed in by the command line
 * @return exit code, almost always 0
*/
int main(int argc, char* argv[])
{

	std::cout.flush();

	Logger::start();
	Settings::start();

#ifdef debug_mode

	Logger::info("Running in debug mode.");
	Logger::debug("Current working directory: {}", fs::current_path().string());
#endif
#ifdef _WIN32
	Logger::info("Current OS is: Windows.");
	Logger::info("Windows debug version will check for memory leaks.");

	//check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

#ifdef __linux__
	//Logger::get() << "Current OS is: Linux\n"
	//	<< "Windows debug version will check for memory leaks\n";
#endif

#ifdef __APPLE__
	//Logger::get() << "Current OS is: Mac OSX\n"
	//	<< "Windows debug version will check for memory leaks\n";
#endif


	///***TODO***///
	//MAKE EVERYTHING USE
	//METERS, PIXELS, AND PERCENTS
	//SO THAT VALUES IN THE LEVEL EDITOR
	//CAN BE IN PIXELS

	//OR CHECK OUT IMGUI

	//CREATE AN ACTOR JSON FILE EDITOR

	BenchmarkLogger::get()->beginBenchmark("Game");
	game();
	BenchmarkLogger::get()->endBenchmark("Game");

	Settings::stop();
	BenchmarkLogger::shutdown();
	Logger::stop();
	return 0;
}