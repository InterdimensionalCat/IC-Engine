#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <exception>
#include <memory>
#include <filesystem>

using namespace sf;
using namespace std;
namespace fs = std::filesystem;

//zero vec
#ifndef Z_VEC
#define Z_VEC Vector2f(0,0)
#endif

#ifndef Z_VECD
#define Z_VECD Vector2<double>(0,0)
#endif

#ifndef Vector2D
//#define Vector2D( _X, _Y ) Vector2<double>(_X, _Y);
#define Vector2D Vector2<double>
#endif

//memory leak check
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

#include "GameEngine2020.h"
#include "InputHandle.h"
#include "StateManager.h"
#include "Renderer.h"

Vector2f lerp(const Vector2f &a, const Vector2f &b, const float t);
float lerp(const float a, const float b, const float t);

ostream & operator<<(ostream &os, const Vector2f &rhs);

ostream & operator<<(ostream &os, const Vector2D &rhs);




struct TextureLoadException : public exception {
	TextureLoadException(const string &filename, const string &path) : filename(filename), path(path) {}
	const char * what() const throw () {
		char* msg = "Texture File ";
		strcat(msg, filename.c_str());
		strcat(msg, " does not exist in ");
		strcat(msg, path.c_str());
		strcat(msg, "!");
		return msg;
	}

	string filename;
	string path;
};

struct TilesetLoadException : public exception {
	TilesetLoadException(const string &filename, const string &path) : filename(filename), path(path) {}
	const char * what() const throw () {
		char* msg = "tsf File ";
		strcat(msg, filename.c_str());
		strcat(msg, " does not exist in ");
		strcat(msg, path.c_str());
		strcat(msg, "!");
		return msg;
	}

	string filename;
	string path;
};

struct MapIOException : public exception {
	MapIOException() {}
	const char * what() const throw () {
		char* msg = "Error loading Map/Tileset file!";
		return msg;
	}

};

template <class T>
struct BadInfinityException : public exception {
	BadInfinityException(T offender) : offender(offender) {}
	const char * what() const throw () {
		char* msg = "Value cannot be infinity!";
		return msg;
		//stringstream st;
		//st << "Value at " << &offender << " cannot be infinity!";
		//string msg = "Value at " + &offender + " cannot be infinity!";
		//const std::string& tmp = st.str();
		//static const char* cstr = tmp.c_str();
		//return cstr;
	}

	T offender;
};