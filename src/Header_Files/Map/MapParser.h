#pragma once
#include "json.hpp"

namespace ic {

	class Scene;

	class MapParser {
	public:
		static void parseMap(const std::string& mapName, Scene& scene);
	};
}