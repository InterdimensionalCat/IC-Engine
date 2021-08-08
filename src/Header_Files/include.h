//include.h
/*
Precompiled header that has macro/preprocessor definintions,
most STL and SFML includes that files need
and a few game related includes that almost every file uses
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <exception>
#include <memory>
#include <string>
#include <filesystem>
#include <variant>
#include <map>
#include <vector>
#include <array>
#include <functional>
#include <queue>
#include <optional>
#include <bitset>
#include <limits>
#include <nlohmann\json.hpp>
#include <initializer_list>

//#include <tmxlite/Map.hpp>
//#include <tmxlite/Layer.hpp>
//#include <tmxlite/TileLayer.hpp>
//#include <tmxlite/ObjectGroup.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

//windows specifc macros/setup
#ifdef _WIN32

///////////////MEMORY LEAK CHECKING/////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/*
 on windows debug mode, new keyword is replaced with a debug-new that 
 provides more info about the object that was created(file, line#, etc)
 to better diagnose memory leaks. Since I mostly use smart pointers nowadays
 not super helpful anymore
*/
//#ifdef _DEBUG
//#define DBG_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
//#else
//#define DBG_NEW new 
//#endif

///////////////////////////////////////////////////////////

#endif

//linux specifc macros/setup
#ifdef __linux__

#endif

//mac specifc macros/setup
#ifdef __APPLE__

#endif


#include <SFML\Graphics.hpp>

#include "Space2D.h"
#include "SFMLHelpers.h"
#include "GameEngine2020.h"
#include "InputHandle.h"
//#include "Renderer.h"
#include "LoggerProvider.h"
#include "SettingsProvider.h"

