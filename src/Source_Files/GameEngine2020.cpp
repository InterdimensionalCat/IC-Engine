//#include "include.h"
//#include "SettingsProvider.h"
//#include "LoggerProvider.h"
//#include "InputHandle.h"
//#include "AudioHandle.h"
//#include "Renderer.h"
//#include "GfxTest.h"

#include "Space2D.h"

using namespace s2d;

void s2dTest() {
	
	//linear type and angular type testing
	Pixels px1 = 100_px;
	Pixels px2 = 5.5_px;

	auto px3 = px1 + px2;
	px3 += px2;

	Meters m1 = 1_mtr;
	Meters m2 = 65_px;

	px3 += m1;
	m2 -= 0.5f;

	m2 *= 2.0f;

	Vec2m vmp(px1, px2);

	Percent pc1 = 1.0_pirad;
	Percent pc2 = 50_pcent;



	//test constructors
	Vec2f v1;
	Vec2f v2(1.0f, 3.0f);
	Vec2f v3(s2d::Point2f(1.0f, 2.0f));
	Vec2f v4(s2d::Point2f(1.0f, 2.0f), s2d::Point2f(1.5f, 1.0f));

	NormVec2f nv1(1.0f, 2.0f);
	NormVec2f nv2(60.0_deg);

	Point2f p1;
	Point2f p2(-3.5f, 2.0f);
	Point2f p3(v2);
	Point2f p4(p2, v3);
	Point2f p5(p2, nv1);

	p1 += p2;
	auto p7 = p2 + p3;
	p1 -= p2;
	auto p8 = p2 - p3;

	p7 *= 2.0f;
	p7 /= 2.0f;

	Dim2f d1;
	Dim2f d2(50.0f, 40.0f);
	Dim2f d3(s2d::Point2f(3.0f, 2.0f));
	Dim2f d4(v2);
	Dim2f d5(NormVec2(1.0f, 0.0f));
	Dim2f d6(s2d::Point2f(1.0f, 1.0f), s2d::Point2f(3.0f, 2.0f));

	Rect2f r1;
	Rect2f r2(1.0f, 3.0f, 2.0f, 5.0f);
	Rect2f r3(Point2f(1.0f, 2.0f), Point2f(5.0f, 4.0f));
	Rect2f r4(Point2f(1.0f, 2.0f), Dim2f(5.0f, 4.0f));
	Rect2f r5(r4, Vec2f(0.5, 0.5), Vec2f(0.5, 0.5));
	Rect2f r6(r4, Dim2<Percent>(40_pcent, 40_pcent), Dim2<Percent>(40_pcent, 40_pcent));

	Poly2f pg1;
	Poly2f pg2({ Point2f(0,0), Point2f(1,0), Point2f(1,1) });
	Poly2f pg3(Point2f(0, 0), Point2f(0, 1), Point2f(1, 1));

	std::cout << (r2 > r3) << (r2 == r3) << "\n";

	Mat3f mt1;


	std::cout << "S2D tests Complete!\n";
}

//using namespace ic;
//using namespace ic::gfx;
//
////static std::shared_ptr<GfxTest> test;
//
//void updateInput(Renderer& renderer) {
//	//renderer.updateInput();
//}
//
////Sends input events to everything that needs it
//void handleInput(InputHandle& input) {
//	test->update(input);
//}
//
////updates all non-input-non-physics game logic
//void updateAI() {}
////updates all physics-related game logic
//void updatePhysics(const float dt) {}
//
////handles audio related stuff
//void updateAudio(AudioHandle& audio) {}
//
////renders game
//void draw(float interpol, Renderer& renderer) {
//	renderer.preRender(interpol);
//
//	test->draw(renderer);
//
//	renderer.postRender();
//}
//
//void game() {
//	//create window, set height, width name, framerate set vsync if enabled
//	auto renderer = std::make_unique<Renderer>();
//	auto audio = std::make_unique<AudioHandle>();
//
//	//Game Loop Objects:
//	std::unique_ptr<sf::Clock> timer;
//	float dt = 0.0f;
//	float currentfps = 0;
//	sf::Clock fpstimer = sf::Clock();
//
//	//initialize clock and gameloop time accumulator
//	timer = std::make_unique<sf::Clock>();
//	double accumulator = 0;
//
//	auto input = std::make_unique<InputHandle>();
//
//	test = std::make_shared<GfxTest>();
//
//	//main game loop
//	while (SettingsProvider::getSetting<bool>("running"))
//	{
//		//update accumulator with time passed
//		double deltaTime = timer->getElapsedTime().asSeconds();
//		accumulator += deltaTime;
//		timer->restart();
//
//		const float targetDT = SettingsProvider::getSetting<float>("targetDT");
//
//
//		if (SettingsProvider::getSetting<TimeStepType>("TimeStepType") == TimeStepType::Variable) {
//			//variable timestep
//
//			updateInput(*renderer);
//			handleInput(*input);
//			updateAI();
//			updatePhysics((float)accumulator);
//			updateAudio(*audio);
//
//			accumulator = 0;
//		}
//		else {
//			//fixed time step
//			while (accumulator >= targetDT) {
//
//				updateInput(*renderer);
//				handleInput(*input);
//				updateAI();
//				updatePhysics(targetDT);
//				updateAudio(*audio);
//
//				accumulator -= targetDT;
//			}
//		}
//
//
//		//draw
//		draw((float)accumulator / targetDT, *renderer);
//	}
//}
//
//void stop() {
//#ifdef debug_mode
//	LoggerProvider::log("Game Closing\n");
//#endif
//	SettingsProvider::setSetting<bool>("running", false);
//	//running = false;
//	//renderer->window->close();
//}

int main(int argc, char *argv[])
{

	std::cout.flush();

#ifdef debug_mode
	//LoggerProvider::log("Running in debug mode", LogSeverity::Debug);
	//LoggerProvider::log("Current working directory: " + fs::current_path().generic_string(), LogSeverity::Info);
#endif

#ifdef _WIN32
	//LoggerProvider::log("Current OS is: Windows\n");
	//LoggerProvider::log("Windows debug version will check for memory leaks\n");
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
	//ic::Scene scene;
	//scene.testActorUID();
	//game();
	s2dTest();
	return 0;
}