//include.h
/*
Precompiled header that has macro/preprocessor definintions,
most STL and SFML includes that files need
and a few game related includes that almost every file uses
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <exception>
#include <memory>
#include <string>
#include <filesystem>

using namespace std;
using namespace sf;

namespace fs = std::filesystem;

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
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

///////////////////////////////////////////////////////////

#endif

//linux specifc macros/setup
#ifdef __linux__

#endif

//mac specifc macros/setup
#ifdef __APPLE__

#endif

#ifndef Z_VEC
#define Z_VEC Vector2f(0,0)
#endif


#include "Space2D.h"
#include "SFMLHelpers.h"
#include "GameEngine2020.h"
#include "InputHandle.h"
#include "StateManager.h"
#include "Renderer.h"

#ifdef debug_mode
struct TextureLoadException : public exception {
	TextureLoadException(const string &filename, const string &path) : filename(filename), path(path) {}
	const char * what() const throw () {
		return "Texture file not found!";
	}

	string filename;
	string path;
};

struct MapIOException : public exception {
	MapIOException() {}
	const char * what() const throw () {
		return "Error loading Map/Tileset file!";
	}

};

template <class T>
struct BadInfinityException : public exception {
	BadInfinityException(T offender) : offender(offender) {}
	const char * what() const throw () {
		return "Value cannot be infinity!";
	}

	T offender;
};
#endif