#pragma once

namespace ic {
	class Texture {
	public:

		Texture(const std::string& filename);
		sf::Texture& getTexture();
		const sf::Texture& getTexture() const;
		std::string getName() const;
	private:
		std::shared_ptr<sf::Texture> tex;
		std::string filename;
	};
}


