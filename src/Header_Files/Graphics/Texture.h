#pragma once
#include <string>
#include <memory>
#include "SFML\Graphics.hpp"

namespace ic::gfx {

	/**
	 * @brief                         RAII wrapper for sf::Textures file loading capabilities
	*/
	class Texture {
	public:

		/**
		 * @brief                     Constructs a new texture loaded from the supplied filename
		 * @param filename            The file name of the texture file to load
		*/
		Texture(const std::string& filename);
		~Texture();

		/**
		 * @brief                     Gets a raw pointer to the sf::Texture object, for use with
		 *                            internal SFML functions only
		 * @return                    The raw sf::Texture pointer
		*/
		sf::Texture* getTexturePtr();

		/**
		 * @brief                     The texture data iteslf
		*/
		std::unique_ptr<sf::Texture> tex;

		/**
		 * @brief                     The texture file name
		*/
		std::string filename;
	};
}