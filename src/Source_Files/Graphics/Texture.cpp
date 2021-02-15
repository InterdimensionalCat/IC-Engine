#include "include.h"
#include "Texture.h"
#include <stdexcept>

using namespace ic::gfx;

Texture::Texture(const std::string& filename) : filename(filename) {
	tex = std::make_unique<sf::Texture>();
	fs::path filepath(fs::current_path());
	filepath /= "resources";
	filepath /= "animations";
	filepath /= filename;
	filepath += ".png";

	LoggerProvider::log("loading texture " + filename + "\n", LogSeverity::Debug);

	if (!tex->loadFromFile(filepath.string())) {
		LoggerProvider::log("file " + filename + " at path " + filepath.string() + " does not exist!\n", LogSeverity::Error);
#ifdef debug_mode
		throw std::logic_error("file " + filename + " at path " + filepath.string() + " does not exist!");
#endif
	}
}

Texture::~Texture() {
	LoggerProvider::log("unloading texture " + filename + "\n", LogSeverity::Debug);
}

sf::Texture* Texture::getTexturePtr() {
	return tex.get();
}