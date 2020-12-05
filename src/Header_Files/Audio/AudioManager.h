#include "include.h"
#include "SFML\Audio.hpp"
#include <queue>
#include <map>
#include <memory>

enum class AudioEventType {
	Load,
	Deload,
	Change,
	PlaySound,
	SetVolume,
};

enum class SoundType {
	Music,
	Sound
};

class AudioEvent {

	AudioEvent(const std::string& soundname, const SoundType& soundtype, const AudioEventType& type) : soundname(soundname) soundtype(soundtype), type(type) {}

	AudioEvent(const std::string& soundname, SoundType&& soundtype, AudioEventType&& type) : soundname(soundname), soundtype(soundtype), type(type) {}

	std::string soundname;
	SoundType soundtype;
	AudioEventType type;
};

class AudioManager {

public:
	AudioManager() {

		fs::path filepath(fs::current_path());
		filepath /= "resources";
		filepath /= "sounds";
		filepath /= "test";
		filepath += ".wav";

		if (!buffer.loadFromFile(filepath.string())) {
#ifdef _DEBUG
			throw AudioLoadException("test", filepath.string());
#endif
		}

		filepath = fs::current_path();
		filepath /= "resources";
		filepath /= "sounds";
		filepath /= "testMusic";
		filepath += ".wav";

		if (!music.openFromFile(filepath.string())) {
#ifdef _DEBUG
			throw AudioLoadException("testMusic", filepath.string());
#endif
		}

		music.setLoop(true);
	}


	void tick(InputHandle* input) {
		if (music.getStatus() != sf::SoundSource::Status::Playing) {
			music.play();
	    }
		if (input->isPressed(Keyboard::U)) {
			sound.setBuffer(buffer);
			sound.play();
		}
		if (input->isPressed(Keyboard::Y)) {
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	std::map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
	std::map<std::string, std::unique_ptr<sf::Music>> musics;
	sf::Music* currentSong;
};