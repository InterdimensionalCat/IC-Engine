#pragma once
#include <string>
#include <memory>
#include "SFML\Graphics.hpp"

namespace ic {
	class Texture {
	public:
		Texture(const std::string& filename);
		~Texture();
		sf::Texture* getTexturePtr();
		std::unique_ptr<sf::Texture> tex;
		std::string filename;
	};
}